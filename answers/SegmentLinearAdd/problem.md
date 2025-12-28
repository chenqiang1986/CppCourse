# Range Add

Given an array of integers which initially starts at 0 for all entries.
Given a list of ranges, each time a range $[l, r]$ is given, then perform the following operations to the numbers in the range:

$data[i] += (i-l+1)$ for $l\le i\le r$.

## Input
The first line contains two integers n and m with $n, m \le 10^5$.
The next m lines contains two integers l and r with $0 \le l, r < n$.

## Output
A line contains the n numbers after all operations above.
