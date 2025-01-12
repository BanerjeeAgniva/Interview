# Killer Quakes Bar Plot Reproduction

## Goal
Reproduce a recent bar plot "Killer Quakes" from September 10, TOI. The source of the data is mentioned as [Our World in Data](https://ourworldindata.org). The goal is to:
1. Acquire data from Our World in Data.
2. Plot an equivalent bar chart from the acquired data.
3. Verify the match (and identify any mismatches).

---

## Details
The plot combines data from two sources available at Our World in Data:
1. A table from the webpage: [The World's Deadliest Earthquakes](https://ourworldindata.org/the-worlds-deadliest-earthquakes).
2. A dataset from the **natural disasters** dataset on Our World in Data servers.

---

## Data Acquisition
1. **Scraping Webpage Data**:
   - Use the `pandas.read_html` method to scrape data from [The World's Deadliest Earthquakes](https://ourworldindata.org/the-worlds-deadliest-earthquakes).
   - Refer to [Pandas documentation on `read_html`](https://pandas.pydata.org/docs/user_guide/io.html#html) for examples.
   - Note: `read_html` returns an array of tables. Extract the relevant table.

2. **Accessing Natural Disasters Dataset**:
   - Use the `owid-catalog` API:
     - Install the package: `pip install owid-catalog`.
     - Import the catalog: `from owid import catalog`.
   - Retrieve the natural disasters dataset:
     - Use `catalog.find('natural_disasters')` to list available datasets.
     - Select the `natural_disasters_yearly` dataset (2nd row in the table): `data.iloc[1].load()`.

---

## Data Preparation and Cleaning
1. **Filter Earthquake Data**:
   - From the natural disasters dataset, filter rows for:
     - **Event type**: Earthquakes.
     - **Year**: 2020 or later.

2. **Remove Irrelevant Data**:
   - Exclude rows for:
     - "World", "European Union (27)", and continents (manually list them or use a library like [a-world-of-countries](https://pypi.org/project/a-world-of-countries/) to retrieve continent names).
     - Groups such as `['Upper-middle-income countries', 'Lower-middle-income countries', 'High-income countries', 'Low-income countries']`.

3. **Sort and Select Top Rows**:
   - Sort the resulting data in descending order.
   - Select the top 5 rows and concatenate them with the scraped dataset.
   - Ensure both datasets have the same column names before concatenation.

4. **Avoid Duplication**:
   - Use `pandas.DataFrame.drop_duplicates(subset=["country", "year"])` to remove duplicate rows.

---

## Visualization
1. **Bar Plot**:
   - Use horizontal bar plots:
     - With Plotly Express: Set colors to differentiate data pre-2020 and post-2020.
     - With Seaborn: Use the `hue` parameter to assign different hues.

2. **Identify Mismatches**:
   - Compare the reproduced chart with the sample plot.
   - Note any mismatches, which may arise from:
     - Manual additions to the data.
     - Typographic errors during manual entry.

---

### Sample Plot
(Refer to the attached example plot for guidance.)

--- 

### Notes
Some mismatches in the plot may occur due to differences in the source data or manual interventions.
