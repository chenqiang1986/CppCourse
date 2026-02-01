https://usaco.org/index.php?page=viewproblem2&cpid=1543

Bessie is designing a nuclear reactor to power Farmer John's lucrative new AI data center business, CowWeave!

The reactor core consists of N
 (1≤N≤2⋅105
) fuel rods, numbered 1
 through N
. The i
-th rod has a "stable operating range" [li,ri]
 (−109≤li≤ri≤109
), meaning it can only generate power if its energy ai
 (chosen by Bessie) satisfies li≤ai≤ri
; otherwise, it sits idle and does not generate power. Moreover, ai
 must always be an integer. Note that ai
 can be any integer, not limited to [−109,109]
.

However, quantum interactions between the rods mean that there are M
 constraints of the form (x,y,z)
 where Bessie must satisfy ax+ay=z
 (1≤x,y≤N
 and −109≤z≤109
) to prevent the reactor from melting down.

Help Bessie find the maximum number of power-generating rods she can achieve in her design without it melting down!

INPUT FORMAT (input arrives from the terminal / stdin):
The first line contains T
 (1≤T≤10
), the number of independent tests. Each test is specified in the following format:
The first line contains the two integers N
 and M
.
The second line contains the N
 integers l1,…,lN
.
The third line contains the N
 integers r1,…,rN
.
The next M
 lines each contain three integers x
, y
, and z
, each representing a constraint.
It is guaranteed that neither the sum of N
 nor the sum of M
 over all tests exceeds 4⋅105
.

OUTPUT FORMAT (print output to the terminal / stdout):
If no choice of rod energies exists that satisfies all constraints, output −1
. Otherwise, output the maximum number of power-generating rods Bessie can achieve.
SAMPLE INPUT:
```
2
3 3
1 2 3
1 2 3
1 1 2
2 2 10
1 1 4
3 2
1 2 3
1 2 3
1 1 2
2 2 10
```
SAMPLE OUTPUT:
```
-1
2
```
In the second test, the constraints require that:
```
a1+a1=2
a2+a2=10
```
Choosing energies a=[1,5,3]
 results in 2
 power-generating rods because:
```
l1=1≤a1≤1=r1
l3=3≤a3≤3=r3
```
and a
 satisfies all required constraints.

SAMPLE INPUT:
```
1
3 2
10 -10 10
10 -10 10
1 2 0
2 3 0
```
SAMPLE OUTPUT:
```
3
```
Choosing rod energies a=[10,−10,10]
 results in 3
 power-generating rods.

SAMPLE INPUT:
```
5
3 3
1 -1 0
2 1 2
1 2 1
1 3 4
2 3 3
1 1
-100
100
1 1 3
1 1
-100
100
1 1 2
1 2
-100
100
1 1 2
1 1 4
1 2
-100
100
1 1 2
1 1 2
```
SAMPLE OUTPUT:
```
2
-1
1
-1
1
```
SCORING:
Input 4: x=y
 for all constraints.
Inputs 5-7: |x−y|=1
 for all constraints.
Inputs 8-10: |x−y|≤1
 for all constraints.
Inputs 11-13: No additional conditions.
Problem credits: Akshaj Arora
