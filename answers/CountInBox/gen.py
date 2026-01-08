import random



n = int(input())
print(2 * n)

for i in range(n):
    x = random.randint(-1000000, 1000000)
    y = random.randint(-1000000, 1000000)
    print("Input", x, y)
    start1 = random.randint(-1000000, 1000000)
    end1 = random.randint(start, 1000000)
    start2 = random.randint(-1000000, 1000000)
    end2 = random.randint(start, 1000000)
    print("Query", start1, end1, start2, end2)
