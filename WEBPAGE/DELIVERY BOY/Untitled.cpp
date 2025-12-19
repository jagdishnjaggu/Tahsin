/*
    ========== Reception ESP32 NFC Pairing (UID -> Firestore) ==========
    Flow: find oldest patients where nfcStatus == "pending" -> wait for NFC tap (RC522)
    -> write nfcToken = UID and nfcStatus = "filled"
*/

// ---------------- Includes ----------------
#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Firebase_ESP_Client.h>

// ---------------- Wi-Fi ----------------
#define WIFI_SSID "Machine"
#define WIFI_PASS "00000000"

// ---------------- Firebase (your project) ----------------
#define API_KEY "AIzaSyCURsgk1KW5JgIdB4xtsgrrSpRt0q1QvEQ"
#define PROJECT_ID "medicine-vending-machine-2dddb"

// ---------------- RC522 Pins (ESP32) ----------------
// SPI: SCK=18, MISO=19, MOSI=23 (default ESP32)
#define SS_PIN 5
#define RST_PIN 22

// ---------------- Globals ----------------
MFRC522 rfid(SS_PIN, RST_PIN);
FirebaseData fbdo;
FirebaseConfig fbConfig;

String currentPatientId = "";
bool waitingForTap = false;

// ---------------- Helpers ----------------
String uidToString(MFRC522::Uid *uid)
{
    String s = "";
    for (byte i = 0; i < uid->size; i++)
    {
        if (uid->uidByte[i] < 0x10)
            s += "0";
        s += String(uid->uidByte[i], HEX);
    }
    s.toUpperCase();
    return s; // e.g., "04A1B2C3D4"
}

void connectWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(400);
        Serial.print(".");
    }
    Serial.print(" connected: ");
    Serial.println(WiFi.localIP());
}

void initFirebase()
{
    fbConfig.api_key = API_KEY;
    fbConfig.project_id = PROJECT_ID;
    Firebase.begin(&fbConfig, nullptr);
    Firebase.reconnectWiFi(true);
}

// Query Firestore for the oldest patient where nfcStatus == "pending" (limit 1)
bool fetchOldestPendingPatient(String &outPatientId)
{
    FirebaseJson q;
    FirebaseJson fromArr, fromObj, where, fieldFilter, field, value, orderByArr, orderByObj, orderField, root;

    fromObj.set("collectionId", "patients");
    fromArr.add(fromObj);

    field.set("fieldPath", "nfcStatus");
    value.set("stringValue", "pending");
    fieldFilter.set("field", field);
    fieldFilter.set("op", "EQUAL");
    fieldFilter.set("value", value);
    where.set("fieldFilter", fieldFilter);

    orderField.set("fieldPath", "createdAt");
    orderByObj.set("field", orderField);
    orderByObj.set("direction", "ASCENDING");
    orderByArr.add(orderByObj);

    root.set("from", fromArr);
    root.set("where", where);
    root.set("orderBy", orderByArr);
    root.set("limit", 1);

    q.set("structuredQuery", root);

    if (!Firebase.Firestore.runQuery(&fbdo, PROJECT_ID, "", q.raw()))
    {
        Serial.printf("runQuery error: %s\n", fbdo.errorReason().c_str());
        return false;
    }

    FirebaseJson res;
    res.setJsonData(fbdo.payload().c_str());

    size_t count = res.iteratorBegin();
    res.iteratorEnd();
    if (count == 0)
    {
        return false;
    }

    String docName;
    res.get(docName, "[0].document.name");
    if (docName.length() == 0)
        return false;

    int lastSlash = docName.lastIndexOf("/");
    if (lastSlash < 0)
        return false;

    outPatientId = docName.substring(lastSlash + 1);
    return outPatientId.length() > 0;
}

// Write nfcToken = uid and nfcStatus = "filled"
bool markFilled(const String &patientId, const String &uid)
{
    String path = "/patients/" + patientId;
    FirebaseJson content;

    content.set("fields.nfcToken.stringValue", uid);
    content.set("fields.nfcStatus.stringValue", "filled");

    bool ok = Firebase.Firestore.patchDocument(&fbdo, PROJECT_ID, "", path.c_str(),
                                               content.raw(),
                                               "nfcToken,nfcStatus");
    if (!ok)
    {
        Serial.printf("patch error: %s\n", fbdo.errorReason().c_str());
    }
    return ok;
}

// ---------------- Arduino ----------------
void setup()
{
    Serial.begin(115200);
    delay(200);

    SPI.begin();
    rfid.PCD_Init(SS_PIN, RST_PIN);
    delay(50);

    connectWiFi();
    initFirebase();

    Serial.println("Reception NFC ESP ready.");
    Serial.println("Ensure Firestore DEV rules allow public read/write while testing.");
}

void loop()
{
    if (currentPatientId == "")
    {
        String pid;
        if (fetchOldestPendingPatient(pid))
        {
            currentPatientId = pid;
            waitingForTap = true;
            Serial.printf("\nPending patient found: %s\n", currentPatientId.c_str());
            Serial.println("Tap a card on the reader to assign UID...");
        }
        else
        {
            delay(400);
            return;
        }
    }

    if (waitingForTap)
    {
        if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
        {
            delay(40);
            return;
        }

        String uid = uidToString(&rfid.uid);
        Serial.printf("Card UID: %s\n", uid.c_str());

        if (markFilled(currentPatientId, uid))
        {
            Serial.println("Saved → nfcStatus=filled");
        }
        else
        {
            Serial.println("Save failed — will retry a new pending patient.");
        }

        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();

        currentPatientId = "";
        waitingForTap = false;

        delay(200);
        return;
    }

    delay(50);
}