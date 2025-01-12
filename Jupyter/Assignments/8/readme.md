```markdown
# Goal: Geo-visualization of Thematic Data Using Choropleth

## Detail:
Use a Choropleth map to show the population variation among the states of India.

## Data Preparation:
Note: Geo-visualization needs geometric information about the geographical location/space. This data may or may not be available with the thematic data. If it is not available in the data file, then the identity of the location/space must be identified by the commonly accepted identity of the geographical location/space. The identity may be simply a name (e.g., Delhi, India) or an ISO code for the state or country. For example, see [ISO 3166-2:IN](https://en.wikipedia.org/wiki/ISO_3166-2:IN) for the ISO code of Indian States, and [ISO 3166 Country Codes](https://en.wikipedia.org/wiki/List_of_ISO_3166_country_codes) for ISO codes for countries.

It is the responsibility of the geo-visualization creator to acquire the geometric data from standard sources and relate the identity of the geographical location/space to the geometrical data.

You may use geometrical information of Indian states and Union territories from [HindustanTimesLabs shapefiles](https://github.com/HindustanTimesLabs/shapefiles).

Attached is a CSV data file containing the estimated 2023 population of Indian states and most Indian Union Territories. The data has been assembled from a table on [FindEasy](https://www.findeasy.in/top-indian-states-by-population/) and guarantees a one-to-one correspondence between the names in the data file and the `properties.ST_NM` key of the feature dictionary of the `IndiaState.json` file (available in the above-mentioned shapefiles folder). The related information will be covered in the class.

## Data Visualization:
You may use `plotly.express` or `geopandas` for creating the choropleth map.

`plotly.express` provides two methods: 
- `px.choropleth`
- `px.choropleth_mapbox`

Find attached two sample plots using `px.choropleth`.
```
