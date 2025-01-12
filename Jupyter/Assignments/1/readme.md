# Assignment 1: Data Acquisition and Cleaning

## Week of Aug 21: Data Acquisition and Inspection
1. Download pin code data in CSV format from [data.gov.in](https://data.gov.in) (search for "all India pincode directory" till the last month).  
2. Read and create a data frame.  
3. Count the number of rows and columns in the data frame.  
4. List the column names.  
5. Count the number of rows with missing values.  

## Week of Aug 28: Data Cleaning
1. Re-read the CSV file with the 'Latitude' and 'Longitude' columns read as strings.  
   - **Hint**: Use the `dtype` parameter in the `read_csv` method.  
2. Remove rows with missing values and reset the indices of the data frame.  
3. Clean the 'Latitude' and 'Longitude' columns and convert them to `float` type.  
   - **Hint**: Use `.astype(float)`.  
   - Check for errors during conversion. Clean and retry the conversion. Repeat the process until the conversion succeeds.
