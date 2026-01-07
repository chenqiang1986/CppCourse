# Left Most In Range
Implement a class to maintain a set of 2-d coordinates $(x, y)$.
The class must have the following two functions:
1. insert(x,y), it will insert $(x,y)$ into the set. -10000000 < x,y < 10000000
2. left_most_in_range(y_min, y_max) should return the minimum value of $x$ for the points in the current set such that $y_\{min} \le y \le y_{max}$.

## Input
1. First line: A integer N, represents the number of operations.
2. 2nd ~ (N+1)-th line: Each line contains an operation either
```
Insert x y
```
or
```
Query y_min y_max
```
## Output
For each query in the input, print the answer left_most_in_range(y_min, y_max).

## Example
### Example Input
```
5
Insert 1 2
Insert 0 6
Insert 3 3
Query 2 3
Query 3 6
```
### Expect Output
```
1
0
```
For "Query 2 3", the two points with y value in this range is $(1,2)$ and $(3,3)$, so minimal x value is 1.

For "Query 3 6", the two points with y value in this range is $(0,6)$ and $(3,3)$, so minimal x value is 0.
