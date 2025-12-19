# Mill Dashboard

A real-time dashboard for monitoring milling operations and machine status in a manufacturing facility.

## Overview

The Mill Dashboard is a web-based interface designed to display real-time information about milling machines, including RPM, temperature readings, and job status. The dashboard provides a comprehensive view of the milling plan and current operations across multiple machines.

## Features

### Real-time Monitoring
- **Live Clock**: Displays current time in HH:MM:SS format
- **Machine Status**: Real-time RPM and temperature readings for 4 machines
- **Job Tracking**: Current and upcoming job information for 7 machines (M1-M7)

### Machine Data
- **Machine 1-4**: Real-time RPM and temperature monitoring
- **Machine M1-M7**: Job status and scheduling information

### Job Information Display
- Grain type being milled
- Quantity being processed
- Coarseness level
- Start and stop times
- Duration of operations
- Next job in queue
- **Timing indicators** for job delays
- **Smart next job display** (skips cleaning/halted jobs when appropriate)

### Status Indicators
- **Milling**: Active milling operations (green)
- **Queue**: Jobs waiting in queue (yellow)
- **No Job**: No active operations (gray)

### Timing Indicators
- **Green Square**: Job is on time (within 5 minutes of scheduled start)
- **Red Square**: Job is delayed (more than 5 minutes past scheduled start)
- **Real-time monitoring** of job timing status

## Technical Stack

- **Frontend**: HTML5, CSS3, JavaScript (ES6+)
- **Real-time Data**: Firebase Realtime Database
- **Database**: Supabase (PostgreSQL)
- **Styling**: Custom CSS with responsive grid layout

## Data Sources

### Firebase Realtime Database
- **URL 1**: `https://mill-live-voltage-default-rtdb.asia-southeast1.firebasedatabase.app/rpm_temp_2.json`
- **URL 2**: `https://mill-live-voltage-default-rtdb.asia-southeast1.firebasedatabase.app/rpm_temp_1.json`

### Supabase Database
- **Table**: `millinglogs_copy`
- **Fields**: machine, status, graintomill, quantity, coarseness, starttime, stoptime, duration

## File Structure

```
TV/
├── index.html          # Main dashboard file
└── logo/
    └── Mill Story logo.png
```

## Setup and Installation

1. **Clone or download** the project files
2. **Open** `index.html` in a web browser
3. **Ensure internet connection** for real-time data fetching

## Configuration

### Firebase Configuration
The dashboard connects to Firebase Realtime Database for machine sensor data:
- RPM and temperature readings
- Automatic refresh every 5 seconds

### Supabase Configuration
The dashboard connects to Supabase for job management data:
- Job status and scheduling
- Automatic refresh every 5 seconds

## Browser Compatibility

- Modern browsers with ES6+ support
- Responsive design for various screen sizes
- Optimized for TV/monitor displays

## Real-time Updates

- **Clock**: Updates every second
- **Machine Data**: Updates every 5 seconds
- **Job Status**: Updates every 5 seconds
- **Timing Indicators**: Updates every 5 seconds

## Customization

### Styling
- Modify CSS variables in the `<style>` section
- Adjust grid layout by modifying `.parent` CSS class
- Customize colors and fonts as needed

### Data Sources
- Update Firebase URLs for different data sources
- Modify Supabase connection details
- Add additional machine monitoring as needed

## Dependencies

- **Supabase JS Client**: Loaded from CDN
- **No additional npm packages required**

## Security Notes

- API keys are exposed in client-side code (consider server-side proxy for production)
- Firebase and Supabase security rules should be properly configured
- Consider implementing authentication for sensitive operations

## Troubleshooting

### Common Issues
1. **No data displayed**: Check internet connection and API endpoints
2. **Layout issues**: Ensure browser supports CSS Grid
3. **Missing logo**: Verify logo file path

### Debug Information
- Check browser console for JavaScript errors
- Verify Firebase and Supabase connection status
- Monitor network requests for data fetching issues

## Recent Updates

### v2.0 - Timing Monitoring System
- **Added timing indicators** for real-time job delay monitoring
- **Enhanced next job display logic** to skip cleaning/halted jobs appropriately
- **Improved visual feedback** with green/red squares for job timing status
- **5-minute tolerance** for job start times

### v1.0 - Initial Release
- Basic dashboard with machine monitoring
- Real-time RPM and temperature display
- Job status tracking and queue management

---

**Date**: 14/7/25  
**Developer**: jagdish
**Email**: jagdishnjaggu@gmail.com  
**GitHub**: jagdishnjaggu.github.io