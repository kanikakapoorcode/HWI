#Easy
You want to buy food from a store. You have a scoring system that uses a unit called taste points.Each time you buy a type of food, you can measureits tastiness by the number of taste points you getfrom that food.You have N types of food. You can buy any type any number of times, as long as the total number of meals does not exceed M.However, you don't want to grow tired of a food if you buy it too often. Therefore, you will get v[i] − d[i] × (ti − 1) taste points when you buy the i-th type of food for the ti-th time.Find the maximum number of taste points you can achieve.

##Approach
🌿 Key Insight

For each food type i, the taste sequence looks like:

v[i], v[i] - d[i], v[i] - 2*d[i], ...

This is a decreasing arithmetic sequence.

So instead of thinking “which food to pick each time,” think:

👉 Pick the top M values from all these sequences combined.

⚡ Efficient Strategy (because M can be huge)

We cannot simulate M steps (since M can be up to 10^9)

So we:

1. Binary Search a Threshold T

Find a value T such that:

There are at least M values ≥ T across all sequences

2. Count how many values ≥ T

For each food:

if v[i] >= T:
    count_i = (v[i] - T) / d[i] + 1
else:
    count_i = 0
3. Compute Total Taste

For each food, sum of its valid terms:

k = count_i
last = v[i] - (k-1)*d[i]
sum_i = k * (v[i] + last) / 2

Add all sum_i.

4. Adjust Extra Terms

If total picked > M:

remove (extra terms) × T

