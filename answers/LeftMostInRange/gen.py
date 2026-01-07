import random



n = int(input())
print(n)

start_range = int(input())
length_range = int(input())

for i in range(n):
    start = random.randint(1, start_range)
    end = start + random.randint(0, length_range)
    print(start, end)
