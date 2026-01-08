# Count In Box
Implement a class to maintain a set of 2-d coordinates $(x, y)$.
The class must have the following two functions:
1. insert(x,y), it will insert $(x,y)$ into the set. $(-10000000 \le x,y \le 10000000)$
2. count($x_\{min}, x_{max}, y_\{min}, y_{max}$) should return count of the points in the current set such that $x_\{min} \le x \le x_{max}$ and $y_\{min} \le y \le y_{max}$.
## Input
1. First line: A integer N, represents the number of operations.
2. 2nd ~ (N+1)-th line: Each line contains an operation either
```
Insert x y
```
or
```
Query x_min x_max y_min y_max
```
## Output
For each query in the input, print the answer count($x_\{min}, x_{max}, y_\{min}, y_{max}$).

## Example
### Example Input
```
4
Input 2 3
Query 1 5 1 5
Input 3 2
Query 1 3 1 2
```
### Expect Output
```
1
1
```
For "Query 1 5 1 5", the point in this range is $(2,3)$.

For "Query 1 3 1 2", the point in this range is $(3,2)$.
