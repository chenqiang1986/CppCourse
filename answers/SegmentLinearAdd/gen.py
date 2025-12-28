from random import randint

n = int(input())
m = int(input())
print(n,m)

for i in range(m):
    start = randint(0, n-1)
    length = randint(0, n-1-start)
    print(start, start+length)