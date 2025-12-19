# Mflow: Packing Dashboard

A real-time packing room dashboard that displays orders for the day, organized by priority, status, and route. Built with HTML, CSS, JavaScript, and Supabase for real-time data synchronization.

## 📋 Table of Contents

- [Features](#features)
- [Technology Stack](#technology-stack)
- [Project Structure](#project-structure)
- [Setup Instructions](#setup-instructions)
- [Database Schema](#database-schema)
- [Order Display Logic](#order-display-logic)
- [Real-time Updates](#real-time-updates)
- [Styling & UI](#styling--ui)
- [Configuration](#configuration)

## ✨ Features

### Core Functionality
- **Real-time Order Display**: Live updates from Supabase database
- **Smart Order Organization**: Orders displayed in priority sequence
- **Route-based Grouping**: Orders grouped by delivery routes (r1, r2, r3, etc.)
- **Status Tracking**: Visual indicators for different order statuses
- **Packing Time Display**: Shows when orders were packed
- **Auto-refresh**: Data updates every 2 seconds without page flicker

### Order Display Sequence
1. **Last 2 Packed Orders** - Most recently completed orders
2. **Priority Orders** - High-priority orders (golden background)
3. **Issued Orders** - Orders with errors/issues (red background)
4. **Route Orders** - Normal orders grouped by route (r1, r2, r3, etc.)
5. **All Packed Orders** - Complete list of packed orders (descending order)

### Visual Indicators
- 🟢 **Green Cards**: Packed orders
- 🟡 **Golden Cards**: Priority orders
- 🔴 **Red Cards**: Issued/error orders
- ⚪ **White Cards**: Normal pending orders

## 🛠 Technology Stack

- **Frontend**: HTML5, CSS3, Vanilla JavaScript (ES6+)
- **Database**: Supabase (PostgreSQL)
- **Real-time**: Supabase Realtime subscriptions
- **Styling**: Custom CSS with responsive design
- **Fonts**: Inter (Google Fonts)
- **Icons**: Unicode emoji icons

## 📁 Project Structure

```
TV/
├── index.html          # Main dashboard file
├── logo/
│   └── Mill Story logo.png  # Company logo
└── README.md          # This documentation
```

## 🚀 Setup Instructions

### Prerequisites
- Modern web browser (Chrome, Firefox, Safari, Edge)
- Internet connection for Supabase and Google Fonts
- No local server required (runs directly in browser)

### Installation
1. Clone or download the project files
2. Open `index.html` in a web browser
3. The dashboard will automatically connect to Supabase and start displaying data

### Database Configuration
The dashboard connects to a Supabase instance with the following configuration:
- **URL**: `https://sipnmwhfzdtqoqszgkmo.supabase.co`
- **Table**: `orders_overall_copy`
- **Real-time**: Enabled for immediate updates

## 🗄 Database Schema

### Table: `orders_overall_copy`

| Column | Type | Description |
|--------|------|-------------|
| `shopify_name` | String | Order identifier |
| `customer_name` | String | Customer name |
| `item_name` | String | Product name |
| `fineness` | String | Product fineness |
| `quantity` | Number | Order quantity |
| `unit` | String | Unit of measurement |
| `weight` | String | Product weight |
| `total` | Number | Order total |
| `packing_status` | String | Status: 'packed', 'priority', 'error', 'pending', 'unpacked' |
| `packing_error_code` | String | Error code if applicable |
| `actual_packed_time` | Timestamp | When order was packed |
| `order_date` | Date | Order creation date |
| `planned_delivery` | Date | Scheduled delivery date |
| `route` | String | Delivery route (r1, r2, r3, etc.) |

## 📊 Order Display Logic

### Data Processing
1. **Fetch Orders**: Retrieves today's orders from Supabase
2. **Group by Order**: Combines multiple items per order
3. **Sort by Route**: Orders sorted numerically (r1, r2, r3, etc.)
4. **Filter by Status**: Separates orders by packing status
5. **Calculate Summary**: Updates summary bar with counts

### Status Categories
- **Packed**: `packing_status === "packed"`
- **Priority**: `packing_status === "priority"`
- **Issued**: `packing_status === "error"` OR `packing_error_code` exists
- **Unpacked**: No status or status is 'pending'/'unpacked'

### Route Sorting
Routes are sorted numerically using regex pattern matching:
```javascript
const getRouteNum = r => r && /^r(\d+)$/i.test(r) ? parseInt(r.slice(1), 10) : Infinity;
```

## 🔄 Real-time Updates

### Update Mechanisms
1. **Supabase Realtime**: Immediate updates on database changes
2. **Polling**: 2-second interval for data refresh
3. **Smart DOM Updates**: Only updates when content changes

### Update Logic
```javascript
// Background refresh every 2 seconds
setInterval(() => {
  fetchOrders({background: true});
}, 2000);

// Real-time subscription
supabase.channel('orders_overall_copy-changes')
  .on('postgres_changes', {...})
  .subscribe();
```

## 🎨 Styling & UI

### Design Principles
- **Responsive Grid**: Auto-fitting cards with minimum width
- **Color-coded Status**: Visual indicators for different order states
- **Modern Typography**: Inter font for clean readability
- **Subtle Shadows**: Card shadows for depth
- **Smooth Transitions**: Hover effects and animations

### CSS Features
- **CSS Grid**: Responsive layout with `grid-template-columns`
- **Flexbox**: Header and card content alignment
- **Custom Properties**: Consistent spacing and colors
- **Media Queries**: Responsive design considerations

### Color Scheme
- **Primary**: #1a1a1a (dark text)
- **Background**: #f7f8fc (light gray)
- **Cards**: #ffffff (white)
- **Priority**: #ffd600 (golden yellow)
- **Packed**: #66bb6a (green)
- **Issued**: #dc3545 (red)

## ⚙️ Configuration

### Supabase Connection
```javascript
const supabase = window.supabase.createClient(
  "https://sipnmwhfzdtqoqszgkmo.supabase.co",
  "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
);
```

### Update Intervals
- **Time Display**: Updates every 1 second
- **Data Refresh**: Updates every 2 seconds
- **Real-time**: Immediate on database changes

### Display Settings
- **Font Size**: Responsive using `vw` units
- **Card Layout**: Auto-fitting grid with 28% minimum width
- **Summary Bar**: Fixed at top with order counts
- **Time Display**: Right-aligned in header

## 🔧 Customization

### Adding New Status Types
1. Add new status to database
2. Update filtering logic in `fetchOrders()`
3. Add corresponding CSS classes
4. Update summary calculations

### Modifying Display Order
Edit the sequence in `fetchOrders()` function:
1. Just packed orders
2. Priority orders
3. Issued orders
4. Route orders
5. All packed orders

### Styling Changes
- Modify CSS variables in `<style>` section
- Update color schemes for different statuses
- Adjust responsive breakpoints as needed

## 📱 Browser Compatibility

- **Chrome**: 80+
- **Firefox**: 75+
- **Safari**: 13+
- **Edge**: 80+

## 🚨 Troubleshooting

### Common Issues
1. **No Data Display**: Check Supabase connection and table permissions
2. **Real-time Not Working**: Verify Supabase realtime is enabled
3. **Styling Issues**: Ensure CSS is loading properly
4. **Performance**: Check for excessive DOM updates

### Debug Mode
Add console logging to `fetchOrders()` function:
```javascript
console.log('Orders fetched:', uniqueOrders);
console.log('Summary:', {totalCount, packedCount, unpackedCount, issuedCount});
```

## 📈 Performance Optimizations

- **Smart DOM Updates**: Only updates when content changes
- **Background Refresh**: Prevents UI flickering
- **Efficient Sorting**: Optimized route sorting algorithm
- **Minimal Re-renders**: Uses content comparison for updates

## 🔒 Security Considerations

- **Read-only Access**: Dashboard only reads data
- **Public API Key**: Uses Supabase anonymous key
- **No Sensitive Data**: Only displays order information
- **CORS Compliant**: Works with standard web security

## 📞 Support

For technical support or feature requests, please contact the development team.

---

**Date**: 10/7/2025  
**Developer**: jagdish
**Email**: jagdishnjaggu@gmail.com  
**GitHub**: jagdishnjaggu.github.io

---

*This dashboard is designed for real-time packing room operations and provides immediate visibility into order status and progress.* 