https://usaco.org/index.php?page=viewproblem2&cpid=116

Problem 2: Cow IDs [Brian Dean, 2012]

Being a secret computer geek, Farmer John labels all of his cows with
binary numbers.  However, he is a bit superstitious, and only labels cows
with binary numbers that have exactly K "1" bits (1 <= K <= 10).  The
leading bit of each label is always a "1" bit, of course.  FJ assigns
labels in increasing numeric order, starting from the smallest possible
valid label -- a K-bit number consisting of all "1" bits.  Unfortunately,
he loses track of his labeling and needs your help: please determine the
Nth label he should assign (1 <= N <= 10^7).

PROBLEM NAME: cowids

INPUT FORMAT:

* Line 1: Two space-separated integers, N and K.

SAMPLE INPUT (file cowids.in):

7 3

INPUT DETAILS:

Among all binary numbers containing exactly 3 "1" bits, FJ wants to output
the 7th in increasing sorted order.

SAMPLE OUTPUT (file cowids.out):

10110
