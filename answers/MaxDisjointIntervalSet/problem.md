# Max Disjoint Interval Set

Given a list of closed intervals \{\[a<sub>n</sub>, b<sub>n</sub>\]\}.
Find the max size of the subset of the given list, such that no intervals in the subset overlaps any other.

## Input
First line: One integer N ($N \le 1000$)

2nd ~ (N+1)th line: Two Integers a<sub>i</sub> b<sub>i</sub>

## Output
One Integer, the max size of the subset.

## Example
Input: 
```
3
1 5
2 3
4 7
```

Output:
```
2
```

Explanation: Take intervals \[2, 3\] and \[4, 7\]
