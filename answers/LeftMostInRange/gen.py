import random



n = int(input())
print(n)

for i in range(n):
    x = random.randint(-10000000, 10000000)
    y = random.randint(-10000000, 10000000)
    print("Insert", x, y)
    start = random.randint(-10000000, 10000000)
    end = random.randint(start, 10000000)
    print("Query", start, end)
