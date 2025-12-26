# Incremental Disjoint Interval Operation

Starting with an empty set, you are given a list of operations, where each operation can be either

1. Union one interval $[a,b)$ into the set.
2. Subtract one interval $[a,b)$ from the set.

The question is to ask you to write a program to output the final total length of the set.

## Input
1. First line contains a number N with $N \le 10^6$.
2. 2nd ~ (N+1)-th line, each line contains a string and two integers $a_i, b_i$, with $0 \le a_i < b_i \le 10^9$.
The string can either be "Union" or "Subtract", and the two integers represent the interval to be union in or subtracted.

## Output
One integer, representing the final total length of the set.

## Example
### Input
```
2
Union 0 3
Subtract 1 2
```
### Output
```
2
```
### Explanation
Subtracting $[1,2)$ from $[0,3)$, we get the set $[0,1) \cup [2,3)$, with total length 2.

### Input
```
3
Union 0 5
Subtract 1 4
Union 2 3
```
### Output
```
3
```
### Explanation
Final set is $[0,1) \cup [2,3) \cup [4,5)$.
