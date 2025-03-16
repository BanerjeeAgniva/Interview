# Minimum Time to Repair Cars

## Solution Approach:
This problem requires us to find the minimum time required to repair all cars given that multiple mechanics can work simultaneously.

## Observations:
### Mechanic Repair Time Formula:
- A mechanic with rank `r` takes `r * n²` minutes to repair `n` cars.
- If `T` is the given time, a mechanic with rank `r` can repair at most `floor(√(T / r))` cars.

### Binary Search on Time:
- The **minimum possible time** is when all cars are repaired instantly (`T=0`).
- The **maximum possible time** is when the slowest mechanic repairs all cars alone (`max(ranks) * cars²`).
- We use **binary search** to find the smallest `T` for which all cars can be repaired.

## Algorithm:
### Binary Search on Time:
1. Set `left = 1` and `right = max(ranks) * cars²` as the search range.
2. For each `mid = (left + right) // 2`, check if all cars can be repaired within `mid` minutes.
3. If **yes**, move `right = mid` to search for a smaller possible time.
4. If **no**, move `left = mid + 1` to increase the time.

### Check Feasibility (Helper Function):
1. Iterate over mechanics and calculate how many cars they can repair in `mid` time.
2. If total repaired cars ≥ `cars`, return `True`.

## Complexity Analysis:
- **Binary Search Range:** `O(log(max(ranks) * cars²))`
- **Checking Feasibility:** `O(n)`, where `n` is the number of mechanics.
- **Total Complexity:** `O(n log(max(ranks) * cars²))` (efficient for large inputs).

