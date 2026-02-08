# Gold Mine Average Time

Given a list of numbers, which represents a list of Gold Mines' initial gold quantify.
For each day, it is allowed for each Gold Mine to move at most 1 gold from itself to its neighbor.
Write a program to calculate the minimum days needed so that all Gold Mines have equal number of gold.

## Input
The first line N ($N \le 10^6$)
The second line contains N numbers $1 \le v[i] \le 10^9$

## Output
A single integer represents the number of days, or -1 if it is impossible to achieve the goal.

## Example
### Input 1
```
3
4 1 4
```
### Output 1
```
1
```
Explanation: Move 1 gold from mine 1 to mine 2, and Move 1 gold from mine 3 to mine 2.



### Input 2
```
3
1 4 1
```
### Output 2
```
2
```
Explanation: Move 1 gold from mine 2 to mine 1, and Move 1 gold from mine 2 to mine 3. 
However the two steps have to happen in different days, because they all initiated from mine 2.
