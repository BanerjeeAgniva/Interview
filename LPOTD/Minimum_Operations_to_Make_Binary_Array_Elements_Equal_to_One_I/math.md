## Greedy Algorithm Proof for Minimum Flips

### 1. Greedy Choice is Optimal

**Claim:** Flipping the first encountered `0` (i.e., when scanning left-to-right) is always part of some optimal solution.

**Exchange Argument:**  
Suppose an optimal solution does not flip the leftmost `0` at index *i*. Then there must be another operation later that flips this `0`. You can “exchange” that later flip with an earlier flip at index *i* without increasing the total number of flips. This means there exists an optimal solution that flips the leftmost `0` as soon as it is encountered.  
This exchange argument ensures that our decision to flip at the first `0` is always safe (optimal).

---

### 2. Inductive Proof

You can formalize the correctness using induction on the array length:

#### Base Case:
For arrays of size `3` (the minimum allowed size), the algorithm clearly does the right thing: if the leftmost element is `0`, it flips the only window available; if not, then no flip is needed. The result is optimal.

#### Inductive Hypothesis:
Assume that for any binary array of length less than `n`, the greedy algorithm produces an optimal number of operations.

#### Inductive Step:
Consider an array of length `n`. Let the first `0` appear at index *i*. By the greedy choice, we flip the window starting at *i*, which affects indices *i, i+1, i+2*.

After this flip, the prefix up to index *i* becomes all `1`s (since we flipped the leftmost `0`), and the remainder of the array is modified in a deterministic way.

Now, the problem reduces to a smaller instance (from index *i+1* onward). By the inductive hypothesis, the greedy algorithm will optimally solve the remaining subproblem.

Thus, the overall number of operations is minimized.

