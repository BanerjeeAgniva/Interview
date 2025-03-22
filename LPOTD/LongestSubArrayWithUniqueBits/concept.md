# Understanding `usedBits & nums[RightmostElementofCurrentWindow] != 0`

checks if the current number (nums[RightmostElementofCurrentWindow]) shares any bits with the numbers already in the subarray.
Consider `nums = [3, 8, 48, 10]`

Assume we're at `nums[3] = 10`.

## **State before adding 10**
- `usedBits = 59` (3 | 8 | 48 = 59, which is `111011` in binary)
- `nums[3] = 10` (`1010` in binary)

### **Conflict Check**
- `usedBits & nums[3] = 111011 & 1010 = 1000` (not 0, so conflict exists)


# Understanding `usedBits ^= nums[LeftmostElementofCurrentWindow];`

## **Key Concept: XOR (`^=`)**
The XOR (exclusive OR) operation follows these rules:

- `A ^ A = 0` (XOR-ing a number with itself removes it)
- `A ^ 0 = A` (XOR-ing with zero does nothing)
- `A ^ B ^ B = A` (XOR-ing the same number twice cancels it out)

Since `usedBits` keeps track of the **bitwise OR** of elements in the window, using `XOR` effectively **removes** elements when needed.

---

## **Example Walkthrough**
Consider the array:

```cpp
nums = [3, 8, 48, 10];
```

At a given point:
- `LeftmostElementofCurrentWindow = 1`
- `RightmostElementofCurrentWindow = 3`
- `usedBits` represents the subarray `[3, 8, 48]`.

### **Initial Bitwise Representation**
| Num  | Binary  |
|------|--------|
| `3`  | `0011` |
| `8`  | `1000` |
| `48` | `110000` |
| `10` | `1010` |

Current `usedBits`:
```cpp
usedBits = 3 | 8 | 48 = 59  // Binary: 111011
```

Now, we try to add `nums[3] = 10` (`1010` in binary).

### **Conflict Check**
```cpp
if ((usedBits & nums[RightmostElementofCurrentWindow]) != 0)
```
- `usedBits & 10 = 111011 & 1010 = 1000` (not 0, so conflict exists).
- We need to remove elements from the left.

### **Removing `nums[1] = 3`**
```cpp
usedBits ^= nums[LeftmostElementofCurrentWindow];  // usedBits ^= 3
LeftmostElementofCurrentWindow++;  // Move window start
```
#### **Bitwise XOR Operation**
```cpp
usedBits = 111011 ^ 0011  // Binary XOR
usedBits = 111000  // 56 in decimal
```
- `3` is **removed** from `usedBits`, but conflict still exists.

### **Removing `nums[2] = 8`**
```cpp
usedBits ^= 8;  // usedBits ^= nums[2]
```
#### **Bitwise XOR Operation**
```cpp
usedBits = 111000 ^ 1000  // Binary XOR
usedBits = 110000  // 48 in decimal
```
- Now, `8` is removed, and `usedBits` contains `48`.

### **Checking Again**
```cpp
if ((usedBits & 10) == 0)  // 48 & 10 = 110000 & 1010 = 0
```
✅ No conflict now! We can add `10`.

### **Final Update**
```cpp
usedBits |= 10;  // Add 10 to the window
```
#### **Bitwise OR Operation**
```cpp
usedBits = 110000 | 1010
usedBits = 111010  // Decimal: 58
```
✅ The new window is `[48, 10]`, and the conflict is resolved.

---

## **Key Takeaways**
- `usedBits |= nums[RightmostElementofCurrentWindow]` **adds** a number using OR.
- `usedBits ^= nums[LeftmostElementofCurrentWindow]` **removes** a number using XOR.
- This technique dynamically adjusts the window **while maintaining the "nice" subarray condition**.

This ensures that we always have the longest valid "nice" subarray while keeping operations efficient.

