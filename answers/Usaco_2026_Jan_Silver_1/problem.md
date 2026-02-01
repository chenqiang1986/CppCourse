https://usaco.org/index.php?page=viewproblem2&cpid=1542

There is a line of cows, initially (i.e. at time t=0
) containing only cow 0
 at position 0
 (here, a cow is at position k
 if there are k
 cows in front of it). At time t
 for t=1,2,3,…
, the cow at position 0 moves to position ⌊t/2⌋
, every cow in positions 1…⌊t/2⌋
 moves forward one position, and cow t
 joins the line at the end of the line (position t
).

Answer Q
 (1≤Q≤105
) independent queries, each of one of the following types:

At what position is cow c
 immediately after time t
 (0≤c≤t≤1018
)?
Which cow is at position x
 immediately after time t
 (0≤x≤t≤1018
)?
INPUT FORMAT (input arrives from the terminal / stdin):
The first line contains Q
, the number of queries.
The next Q
 lines each contain three integers specifying a query either of the form "1 c t" or "2 x t."

OUTPUT FORMAT (print output to the terminal / stdout):
Output the answer to each query on a separate line.
SAMPLE INPUT:
```
2
1 4 9
2 2 9
```
SAMPLE OUTPUT:
```
2
4
```
Lineups immediately after various times:
```
t = 0 | 0
t = 1 | 0 1
t = 2 | 1 0 2
t = 3 | 0 1 2 3
t = 4 | 1 2 0 3 4
t = 5 | 2 0 1 3 4 5
t = 6 | 0 1 3 2 4 5 6
t = 7 | 1 3 2 0 4 5 6 7
t = 8 | 3 2 0 4 1 5 6 7 8
t = 9 | 2 0 4 1 3 5 6 7 8 9
```
Immediately after t=9
, the location of cow 4
 is 2
, and the cow located at position 2
 is 4
.

SAMPLE INPUT:
```
22
1 0 9
1 1 9
1 2 9
1 3 9
1 4 9
1 5 9
1 6 9
1 7 9
1 8 9
1 9 9
2 0 9
2 1 9
2 2 9
2 3 9
2 4 9
2 5 9
2 6 9
2 7 9
2 8 9
2 9 9
1 0 1000000000000000000
2 0 1000000000000000000
```
SAMPLE OUTPUT:
```
1
3
0
4
2
5
6
7
8
9
2
0
4
1
3
5
6
7
8
9
483992463350322770
148148148148148148
```
SCORING:
Input 3: Q≤1000,t≤100
Input 4: t≤5000
Inputs 5-8: All queries are of type 1.
Inputs 9-12: All queries are of type 2.
Problem credits: Agastya Goel
