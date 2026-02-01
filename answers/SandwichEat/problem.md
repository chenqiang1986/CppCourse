# Min Sandwich Eat

A grid of N*M sandwiches is given, with each sqare sandwich being cut into half through one of the diagonal.

Namely we call the big square sandwich either Z sandwich or N sandwich, and a sqaure sandwich is always composed of two small triangle sub-sandwiches.

Now there is some restrictions to take out and eat a sub-sandwich, you can take out a sub-sandwich A if either

1. Both sandwiches adjacent to the sub-sandwich A's two legs are taken.
2. The sub-sandwich sharing the hypotenure with sub-sandwitch A is taken out.

## Input
1. First line two integers N, M
2. Next N lines, each line M charactars, either 'N' or 'Z'

## Output
N lines, with each line M integers

output[i][j] means the minimum number of sandwiches to be taken out in order to take out sandwich[i][j]

or output[i][j]=-1 if sandwich[i][j] is not able to be taken out.

## Example
Input:
```
2 3
NZN
ZZN
```
Output:
```
4 3 0
3 2 1
```
