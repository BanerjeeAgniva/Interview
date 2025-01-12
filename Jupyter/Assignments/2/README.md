
# Data Analysis and Visualization

## Data Acquisition and Inspection
1. **Read Selected Columns**:  
   - Extract only the `Gender` and `Height` columns from the attached Excel file.  
   - Use the following code snippet:  
     ```python
     df = pd.read_excel(<filename>, usecols=<list of columns>)
     ```
   - Ensure the `openpyxl` package is installed before using `pandas.read_excel`.  
     ```bash
     pip install openpyxl
     ```
2. **Column Name Check**:  
   - Verify the exact name of the `Height` column in the dataset.  
3. **Rename Columns (Optional)**:  
   - Use the `pandas.rename` method to shorten column names for convenience:  
     ```python
     df.rename(columns={"Original Column Name": "New Name"}, inplace=True)
     ```
   - Note: The `rename` method does not update the original DataFrame unless `inplace=True` is specified.  
   - Always use the original column name as the axis label for consistency.

---

## Data Cleaning
1. **Uniformity in Gender Column**:  
   - Ensure uniformity in the `Gender` column values (e.g., convert all values to the same case).  
   - Use a `pandas` function to address inconsistencies such as "Male" and "male".

---

## Data Visualization
1. **Required Plots**:  
   - Create the following distribution plots for the dataset:
     - Histogram
     - Box Plot
     - Violin Plot  
2. **Separate Gender Distributions**:  
   - The plots must show the distributions of `Male` and `Female` heights separately, potentially overlapping on the same plot.  
3. **Visualization Libraries**:  
   - Use **Plotly Express** or **Seaborn** for the visualizations.

---

## Dataset Information
- The dataset contains the following features:
  - **Height**, **Weight**, and 4 fingerprint measurements (length, width, area, and circumference).
- Data was collected from 200 participants to perform regression analysis and assess the relationship between fingerprint size and physical stature.
- Dataset Source:  
  [Loughborough University Repository](https://repository.lboro.ac.uk/articles/dataset/Height_weight_and_fingerprint_measurements_collected_from_200_participants/7539206)
