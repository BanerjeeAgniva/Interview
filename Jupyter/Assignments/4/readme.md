# Live Access to NSE Market Data using `nsepython`

## Goal
Access live NSE market data using the `nsepython` package. Acquire and compare the relative changes of the following NIFTY index data over the last 9 years:  
- **NIFTY 50**  
- **NIFTY BANK**  
- **NIFTY IT**

---

## Details

### Data Acquisition
1. Install the `nsepython` package.  
2. Use its `index_total_returns` method to acquire historical index data for the following funds:  
   - Symbols: `NIFTY 50`, `NIFTY BANK`, `NIFTY IT`  
   - **Start Date**: `01-May-2014`  
   - **End Date**: `10-Sept-2023`  
3. Refer to the [nsepython documentation](https://unofficed.com/nse-python/documentation/) for details on implementation.

---

### Data Cleaning and Preparation
1. For each acquired timeseries index data:
   - Compute the relative percent change in the index return value from the start date.  
   - Formula:  
     ```
     Percent Change = 100 * (Return at the date of interest - Return at the start date) / Return at the start date
     ```
2. Combine the updated index data into a single data frame.  
3. Rename columns to clearly distinguish the relative percent change data for the three index funds.

---

### Data Visualization
- Use **Plotly Express** or **Seaborn** to create line plots.  
- Display all three index funds on a single chart for visual comparison.
