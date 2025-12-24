# Flipping Query
Initially you have a list of integer 0 with length N.

We have two operations:

1. Flipping a segment in the list. Flipping means either switch 0 to 1, or 1 to 0.
2. Query a specific position, where you should return the value at that point.



## Input
First line: One integer N ($N \le 10000$)

Second line: One integer M ($M \le 10000$)

Next M lines: A String followed by one or two integers either
```
Query <position>
```
or
```
Flip <start position> <end position>
```
## Output
For each `Query` operation in the input file, use a line to print the value at the requested position.

Example:
```
6
4
Flip 2 4 // Assume the 0-indexed and both end inclusive 
Query 3
Flip 1 5
Query 4
```

1. Initially: 0 0 0 0 0 0
2. Flip 2 4:  0 0 1 1 1 0
3. Query 3: Print 1
4. Flip 1 5:  0 1 0 0 0 1
5. Query 4: Print 0

So the output should be
```
1
0
```
