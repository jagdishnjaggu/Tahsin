# MF: Dispatching Dashboard

A real-time dispatching dashboard for Mill Story operations that displays orders by route with live updates and professional statistics tracking.

## 🚀 Features

### Real-time Dashboard
- **Live Updates**: Real-time order status updates via Supabase subscriptions
- **Dynamic Layout**: Automatically adjusts columns based on number of routes (2 routes = 2 columns, 6 routes = 6 columns)
- **Professional UI**: Clean, modern interface with Inter font and professional styling

### Order Management
- **Route-based Display**: Orders grouped by delivery routes
- **Customer Grouping**: Multiple items from same customer displayed as single order card
- **Status Tracking**: Dual status display (packing + loading) for each order
- **Item Details**: Individual items with quantities, weights, and specifications

### Statistics Dashboard
- **Total orders**: Count of all customers with orders for today
- **Assigned orders**: Customers with orders assigned to routes
- **total Packed**: Customers with all orders packed
- **total Loaded**: Customers with all orders loaded  
- **Delivered orders**: Customers with all orders delivered

### Visual Design
- **Professional Header**: Logo, title, statistics, and live date/time
- **Status Indicators**: Color-coded chips for packing and loading status
- **Responsive Layout**: Adapts to different screen sizes
- **Clean Typography**: Inter font family for professional appearance

## 📊 Data Structure

### Order Fields
- `shopify_name`: Customer name
- `route`: Delivery route assignment
- `assigned_to`: Driver/person assigned to route
- `packing_status`: 'packed' or 'unpacked'
- `loading_status`: 'loaded' or 'not loaded'
- `delivery_status`: 'delivered' or 'not delivered'
- `planned_delivery`: Delivery date (YYYY-MM-DD format)
- `item_name`: Product name
- `fineness`: Product specification
- `quantity`: Item quantity
- `weight`: Item weight
- `unit`: Weight unit (kg/g)

### Status Logic
- **Customer Status**: Based on ALL orders for that customer
- **Route Assignment**: Orders must have non-empty route value
- **Date Filtering**: Only shows orders for today's delivery date

## 🛠️ Technical Details

### Frontend Technologies
- **HTML5**: Semantic markup
- **CSS3**: Grid layout, Flexbox, custom styling
- **JavaScript**: ES6+ syntax, async/await
- **Supabase**: Real-time database integration

### Key Components
- **Grid Layout**: `repeat(auto-fit, minmax(450px, 1fr))` for dynamic columns
- **Real-time Updates**: Supabase PostgreSQL change subscriptions
- **Date Filtering**: Automatic filtering for today's delivery date
- **Status Calculation**: Customer-level status aggregation

### Database Integration
- **Supabase URL**: `https://sipnmwhfzdtqoqszgkmo.supabase.co`
- **Table**: `orders_overall_copy`
- **Real-time**: PostgreSQL change notifications
- **Authentication**: Anonymous access for dashboard

## 📱 Responsive Design

### Breakpoints
- **Desktop**: Full 4-column layout (or more based on routes)
- **Tablet**: Adaptive column sizing
- **Mobile**: Single column with scrollable content

### Grid System
- **Minimum Column Width**: 450px (1.5x wider for better readability)
- **Auto-fit**: Automatically creates optimal number of columns
- **Header Span**: Spans all columns (`grid-column: 1 / -1`)

## 🎨 UI Components

### Header Bar
- **Logo**: Mill Story branding
- **Title**: "MF: Dispatching"
- **Statistics**: Live counts with professional styling
- **DateTime**: Live clock with full date/time

### Route Cards
- **Header**: Route name with driver assignment
- **Order Count**: Number of customers in route
- **Order Cards**: Individual customer orders with items

### Order Cards
- **Customer Name**: Prominent display
- **Dual Status**: Packing and loading status chips
- **Item List**: Individual items with quantities and weights
- **Total Summary**: Combined weight and item count

### Status Indicators
- **Packing**: Green (packed) / Gray (unpacked)
- **Loading**: Blue (loaded) / Amber (not loaded)
- **Icons**: Material Icons for visual clarity

## 🔄 Real-time Features

### Live Updates
- **Database Changes**: Automatic refresh on order updates
- **Status Changes**: Real-time status indicator updates
- **Statistics**: Live count updates
- **Visual Feedback**: Refresh indicator during updates

### Auto-refresh
- **Backup Timer**: 30-second fallback refresh
- **Smart Updates**: Only refreshes when relevant data changes
- **Performance**: Efficient updates without full page reload

## 📋 Setup Instructions

### Prerequisites
- Modern web browser with JavaScript enabled
- Internet connection for Supabase integration
- Access to Supabase database

### Installation
1. Clone or download the project files
2. Ensure `index.html` and `logo/` folder are in the same directory
3. Open `index.html` in a web browser
4. Dashboard will automatically connect to Supabase and load data

### Configuration
- **Database**: Update Supabase URL and key if needed
- **Logo**: Replace `logo/Mill Story logo.png` with your logo
- **Styling**: Modify CSS variables for custom theming

## 🔧 Customization

### Colors
- **Primary**: Blue (#2563eb) for headers and accents
- **Success**: Green (#2f855a) for packed status
- **Warning**: Amber (#d97706) for not loaded status
- **Neutral**: Gray (#64748b) for secondary text

### Layout
- **Column Width**: Adjust `minmax(450px, 1fr)` for different widths
- **Header Height**: Modify padding in `.div1`
- **Card Spacing**: Adjust gap values in grid and flex layouts

### Statistics
- **Labels**: Modify stat labels in `updateHeaderStats()`
- **Order**: Change display order of statistics
- **Formatting**: Customize number formatting and units

## 📈 Performance

### Optimization
- **Efficient Queries**: Single database query with date filtering
- **Smart Updates**: Only refresh when relevant data changes
- **Minimal DOM**: Dynamic element creation and cleanup
- **CSS Grid**: Hardware-accelerated layout rendering

### Monitoring
- **Console Logs**: Detailed logging for debugging
- **Error Handling**: Graceful error display and recovery
- **Loading States**: Clear loading indicators

## 🚨 Error Handling

### Connection Issues
- **Supabase Timeout**: Automatic retry with exponential backoff
- **Network Errors**: User-friendly error messages
- **Data Loading**: Fallback to cached data when possible

### Data Validation
- **Missing Fields**: Graceful handling of incomplete data
- **Date Formatting**: Robust date parsing and display
- **Status Logic**: Safe status calculation with fallbacks

## 📝 Changelog

### Version 1.0
- Initial release with real-time dashboard
- Dynamic route-based layout
- Professional statistics tracking
- Dual status display (packing + loading)
- Responsive design with modern UI

## 👥 Contributing

### Development
- Follow existing code style and patterns
- Test changes across different screen sizes
- Ensure real-time updates continue working
- Update documentation for new features

### Reporting Issues
- Include browser and OS information
- Describe steps to reproduce
- Provide console error logs if available

## 📄 License

This project is proprietary software for Mill Story operations.

---

**Date**: 10/7/2025  
**Developer**: jagdish
**Email**: jagdishnjaggu@gmail.com  
**GitHub**: jagdishnjaggu.github.io