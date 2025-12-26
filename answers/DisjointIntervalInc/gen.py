import random

size_range=int(input())
start_range=int(input())
length_range=int(input())

n = random.randint(1, size_range)
print(n)

for i in range(n):
    op = "Union" if random.randint(0,1)==0 else "Subtract"
    start = random.randint(0, start_range)
    end = start + random.randint(1, length_range)
    print(op, start, end)