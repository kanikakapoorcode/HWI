
# 🍽️ Maximum Taste Points Problem

## 🧾 Problem Statement

You want to buy food from a store. Each food gives you **taste points**.

* There are **N types of food**
* You can buy at most **M meals total**
* You can buy the same food multiple times

However, the taste reduces if you repeat the same food:

[
\text{Taste for i-th food at } t_i\text{-th time} = v[i] - d[i] \times (t_i - 1)
]

👉 Your goal is to **maximize total taste points**.

---

## 🌿 Key Insight

For each food type `i`, the taste forms a sequence:

```
v[i], v[i] - d[i], v[i] - 2*d[i], ...
```

This is a **decreasing arithmetic sequence**.

👉 Instead of choosing foods step-by-step:

**Think of all possible values and pick the top M values.**

---

## ⚡ Efficient Approach

Since `M` can be very large (up to (10^9)), we **cannot simulate directly**.

We use **Binary Search**.

---

## 🔍 Step 1: Binary Search on Threshold `T`

Find a value `T` such that:

* At least **M values ≥ T** exist across all sequences

---

## 🔢 Step 2: Count values ≥ T

For each food:

```cpp
if (v[i] >= T)
    count_i = (v[i] - T) / d[i] + 1;
else
    count_i = 0;
```

Total count = sum of all `count_i`

---

## ➕ Step 3: Compute Total Taste

For each food:

```cpp
k = count_i
last = v[i] - (k - 1) * d[i]
sum_i = k * (v[i] + last) / 2
```

Add all `sum_i` to get total.

---

## ⚖️ Step 4: Adjust Extra Values

If total picked values > M:

```cpp
total -= (extra_count) * T;
```

---

## 🧠 Intuition

You are not choosing foods one by one…

✨ You are collecting the **top M tastiest moments**
from all food types combined.

---

## 🌸 Summary

* Convert problem → **pick top M values**
* Use **binary search on answer**
* Use **math to count + sum efficiently**


