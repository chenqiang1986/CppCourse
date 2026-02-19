# Min Sum From Lists
Given $k$ lists, each list have $c_i$ integers, namely $a_{ij}$.
Bessie is allowed to take one number from each list and take sum.
Find the 1st ~ N-th smallest result Bessie can get.

## Input
First line two integers $k \le 10^5$ and $N \le 10^5$.
Next k lines, each line starts with $c_i$, followed by $c_i$ integers $a_{ij}$, with $\sum{c_i} \le 3*10^5$

## Output
The list of N numbers from smallest result Bessie can get to the N-th result.


## Example
```
2 3
3 1 3 5
3 1 3 5
```
Output
```
2 4 4
```
The min is $1+1=2$, the second and third smallest are $1+3=3+1=4$
