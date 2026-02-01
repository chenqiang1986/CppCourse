# Decipher

Given a list of positive integers, here is the Cipher process.

Say the original list is [4,3,1,2]:

1. Prepend the list with 0, we get [0,4,3,1,2]
2. Generate all rotations of the list we get
```
[0,4,3,1,2]
[4,3,1,2,0]
[3,1,2,0,4]
[1,2,0,4,3]
[2,0,4,3,1]
```
3. Sort those rotations in dictionary order
```
[0,4,3,1,2]
[1,2,0,4,3]
[2,0,4,3,1]
[3,1,2,0,4]
[4,3,1,2,0]
```
4. Take the last element from the above list we get
```
[2,3,1,4,0]
```
This is the ciphered list.

Your task is to write a program which reads the ciphered list, and outputs the original list.

## Input
1. First line, a integer N >= 2
2. Second line has N integers, represents the ciphered list.

## Output
One line with (N-1) integers representing the original list.
