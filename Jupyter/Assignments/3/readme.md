# Time-Series Visualization of Local Monthly Temperatures

## Goal
Create a time-series visualization of local monthly temperatures over a few years.

---

## Data Source
- **URL**: [Telangana Temperature Data (2013-2017)](https://data.telengana.gov.in/dataset/telengana-temperature-data-2013-2017)

---

## Data Acquisition

1. **Downloading Data**:  
   - Directly download the Maximum and Minimum datasets from the [source URL](https://data.telengana.gov.in/dataset/62a1cc18-7613-460b-a0b1-4b71c78fa1ce/api).  
   - Alternatively, use Python's `requests` library and query the metadata using the API:
     ```python
     import requests
     import pandas as pd

     # Fetch metadata
     r = requests.get("https://data.telangana.gov.in/api/1/metastore/schemas/dataset/items/62a1cc18-7613-460b-a0b1-4b71c78fa1ce")
     dataInfo = r.json()

     # Read datasets
     df_max = pd.read_csv(dataInfo["distribution"][0]["downloadURL"])
     df_min = pd.read_csv(dataInfo["distribution"][1]["downloadURL"])
     ```

---

## Data Preparation and Cleaning

1. **Extract Relevant Rows**:  
   - Filter rows corresponding to the **Medchal district** and **Kapra Mandal** from both data frames.  
   - Combine the rows into a single DataFrame if needed for visualization.

2. **Transpose Data**:  
   - Use Pandas `transpose` (`T`) to switch table columns into rows and rows into columns:  
     ```python
     df_transposed = df.T
     ```

3. **Convert Date Format**:  
   - Transform the months and year data into Pandas `Datetime` format:  
     ```python
     df['date'] = pd.to_datetime(df[['Year', 'Month']].astype(str).agg('-'.join, axis=1))
     ```

---

## Data Visualization

1. **Line Plots**:  
   - Use either **Plotly Express** or **Seaborn** to create line plots that display the minimum and maximum temperatures for the months and years available in the dataset.
     ```python
     import plotly.express as px
     import seaborn as sns
     import matplotlib.pyplot as plt

     # Plotly Express
     fig = px.line(df, x="date", y=["Max Temperature", "Min Temperature"], title="Monthly Temperatures")
     fig.show()

     # Seaborn
     sns.lineplot(data=df, x="date", y="Max Temperature", label="Max Temp")
     sns.lineplot(data=df, x="date", y="Min Temperature", label="Min Temp")
     plt.title("Monthly Temperatures")
     plt.xlabel("Date")
     plt.ylabel("Temperature (°C)")
     plt.legend()
     plt.show()
     ```

2. **Insights**:  
   - Ensure the plot clearly distinguishes between the **maximum** and **minimum** temperature trends over the available years.

---

