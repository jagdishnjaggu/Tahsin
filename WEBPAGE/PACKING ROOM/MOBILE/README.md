# MFlow: Packing Interface

A real-time mobile interface for managing order packing operations at Mill Story. This web application provides a streamlined view of today's orders with live updates and status management.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Technical Stack](#technical-stack)
- [Database Schema](#database-schema)
- [Order Display Logic](#order-display-logic)
- [Authentication & Credentials](#authentication--credentials)
- [Real-time Updates](#real-time-updates)
- [Order Status Management](#order-status-management)
- [Mobile-First Design](#mobile-first-design)
- [File Structure](#file-structure)
- [Setup & Deployment](#setup--deployment)
- [API Endpoints](#api-endpoints)
- [Troubleshooting](#troubleshooting)

## 🎯 Overview

The MFlow: Packing Interface is a mobile-optimized web application that displays today's delivery orders in a structured, easy-to-manage format. It provides real-time updates, status management, and a clean interface for packing room operations.

## ✨ Features

### Core Functionality
- **Real-time Order Display**: Live updates of today's orders
- **Status Management**: Mark orders as packed or report issues
- **Priority Handling**: Special handling for priority orders
- **Route-based Organization**: Orders grouped by delivery routes
- **Mobile-Optimized**: Touch-friendly interface for mobile devices
- **Auto-refresh**: Background updates every 2 seconds
- **Live Clock**: Real-time date and time display

### Order Categories
1. **Last 2 Packed Orders** - Recently completed orders at the top
2. **Priority Orders** - High-priority orders with special styling
3. **Issued Orders** - Orders with reported problems
4. **Route Orders** - Normal orders grouped by delivery route (r1, r2, r3, etc.)
5. **All Packed Orders** - Complete list of packed orders at the bottom

### Visual Indicators
- **Priority Orders**: Yellow gradient background with "PRIORITY" label
- **Issued Orders**: Red background with error styling
- **Packed Orders**: Green checkmark with packing time
- **Route Sorting**: Numerical order (r1, r2, r3, etc.)

## 🛠 Technical Stack

- **Frontend**: Vanilla HTML, CSS, JavaScript
- **Database**: Supabase (PostgreSQL)
- **Real-time**: Supabase Realtime subscriptions
- **Styling**: Custom CSS with mobile-first design
- **Fonts**: Inter (Google Fonts)
- **Icons**: Unicode emoji icons

## 🗄 Database Schema

### Table: `orders_overall_copy`

| Column | Type | Description |
|--------|------|-------------|
| `shopify_name` | TEXT | Unique order identifier |
| `customer_name` | TEXT | Customer name |
| `item_name` | TEXT | Product name |
| `fineness` | TEXT | Product specification |
| `quantity` | NUMERIC | Order quantity |
| `unit` | TEXT | Unit of measurement |
| `weight` | TEXT | Weight information |
| `total` | NUMERIC | Total value |
| `packing_status` | TEXT | Current packing status |
| `packing_error_code` | TEXT | Error code if issues |
| `actual_packed_time` | TIMESTAMP | When order was packed |
| `order_date` | DATE | Original order date |
| `planned_delivery` | DATE | Scheduled delivery date |
| `route` | TEXT | Delivery route (r1, r2, etc.) |

### Status Values
- `pending` / `unpacked` / `""` - Normal orders
- `packed` - Completed orders
- `priority` - High-priority orders
- `error` - Orders with issues
- `delayed` - Delayed orders

## 📊 Order Display Logic

### 1. Data Fetching
```javascript
// Fetch today's orders
const today = new Date().toISOString().split("T")[0];
const { data: allOrders } = await supabase
  .from("orders_overall_copy")
  .select("*")
  .eq("planned_delivery", today);
```

### 2. Order Grouping
- **Unique Orders**: Grouped by `shopify_name` to avoid duplicates
- **Status Categories**: Separated by packing status
- **Route Sorting**: Numerical sorting of routes (r1, r2, r3, etc.)

### 3. Display Sequence
1. **Last 2 Packed Orders** - Most recently packed
2. **Priority Orders** - All priority orders
3. **Issued Orders** - All orders with errors
4. **Route Orders** - Normal orders by route
5. **All Packed Orders** - Complete packed list

## 🔐 Authentication & Credentials

### Supabase Configuration
```javascript
const supabase = window.supabase.createClient(
  "https://sipnmwhfzdtqoqszgkmo.supabase.co",
  "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6InNpcG5td2hmemR0cW9xc3pna21vIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NDkxMjA4NzQsImV4cCI6MjA2NDY5Njg3NH0.0i9SvYgkgv6BtN2JjZwTJhnPsIkDPD-5BP6uvky6v9M"
);
```

### Security Notes
- Uses Supabase anonymous role
- Read-only access to `orders_overall_copy` table
- Update permissions for status changes
- No sensitive data exposure

## 🔄 Real-time Updates

### Background Refresh
```javascript
// Background refresh every 2 seconds
setInterval(() => {
  console.log('Background refresh...');
  fetchOrders();
}, 2000);
```

### Supabase Realtime
```javascript
// Real-time subscription
ordersSubscription = supabase
  .channel('orders_overall_copy-changes')
  .on('postgres_changes', {
    event: '*',
    schema: 'public',
    table: 'orders_overall_copy',
    filter: `planned_delivery=eq.${today}`
  }, (payload) => {
    fetchOrders();
  })
  .subscribe();
```

## 📱 Order Status Management

### Mark as Packed
```javascript
async function markAsPacked(shopifyName) {
  const { error } = await supabase
    .from("orders_overall_copy")
    .update({
      packing_status: "packed",
      packing_error_code: null,
      actual_packed_time: new Date().toISOString()
    })
    .eq("shopify_name", shopifyName)
    .eq("planned_delivery", today);
}
```

### Report Issue
```javascript
async function markAsIssue(shopifyName) {
  const { error } = await supabase
    .from("orders_overall_copy")
    .update({
      packing_status: "error",
      packing_error_code: "manual_issue"
    })
    .eq("shopify_name", shopifyName)
    .eq("planned_delivery", today);
}
```

## 📱 Mobile-First Design

### Responsive Features
- **Touch-friendly buttons**: Large, easy-to-tap buttons
- **Mobile-optimized layout**: Single column design
- **Sticky header**: Always visible navigation
- **Fixed refresh button**: Easy access to manual refresh
- **Optimized typography**: Readable on small screens

### CSS Breakpoints
```css
@media (max-width: 480px) {
  .summary-grid { grid-template-columns: 1fr; }
  .title { font-size: 1rem; }
  .order-card { margin-bottom: 0.6rem; }
}
```

## 📁 File Structure

```
MOBILE/
├── index.html          # Main application file
├── README.md          # This documentation
└── logo/
    └── Mill Story logo.png  # Company logo
```

## 🚀 Setup & Deployment

### Local Development
1. Clone or download the files
2. Open `index.html` in a web browser
3. Ensure internet connection for Supabase access
4. Test on mobile device or mobile browser view

### Production Deployment
1. Upload files to web server
2. Ensure HTTPS for Supabase connections
3. Test on actual mobile devices
4. Monitor console for any errors

### Requirements
- Modern web browser with JavaScript enabled
- Internet connection for Supabase access
- Mobile device or mobile browser view for optimal experience

## 🔌 API Endpoints

### Supabase Operations

#### Read Operations
```javascript
// Fetch today's orders
.from("orders_overall_copy")
.select("*")
.eq("planned_delivery", today)
```

#### Update Operations
```javascript
// Mark as packed
.update({
  packing_status: "packed",
  packing_error_code: null,
  actual_packed_time: currentTime
})
.eq("shopify_name", shopifyName)
.eq("planned_delivery", today)

// Mark as issue
.update({
  packing_status: "error",
  packing_error_code: "manual_issue"
})
.eq("shopify_name", shopifyName)
.eq("planned_delivery", today)
```

## 🐛 Troubleshooting

### Common Issues

#### Data Not Loading
- Check internet connection
- Verify Supabase credentials
- Check browser console for errors
- Ensure today's date has orders

#### Real-time Updates Not Working
- Check Supabase realtime subscription
- Verify database permissions
- Check browser console for connection errors

#### Mobile Display Issues
- Test in mobile browser view
- Check viewport meta tag
- Verify CSS media queries

#### Performance Issues
- Reduce background refresh interval
- Check for memory leaks
- Monitor network requests

### Debug Information
- Console logs show background refresh timing
- Network tab shows Supabase requests
- Real-time subscription status in console

## 📝 Last Updated

**Date**: 10/7/2025  
**Developer**: jagdish
**Email**: jagdishnjaggu@gmail.com  
**GitHub**: jagdishnjaggu.github.io

---

**Note**: This interface is designed for internal Mill Story operations and should be used on secure networks. All database operations are logged and monitored for security purposes. 