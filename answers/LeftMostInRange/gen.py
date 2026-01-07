import random



n = int(input())
print(n)

start_range = int(input())
length_range = int(input())
y_range = int(input())

for i in range(n):
    x = random.randint(-10000000, 10000000)
    y = random.randint(-y_range, y_range)
    print("Insert", x, y)
    start = random.randint(1, start_range)
    end = start + random.randint(0, length_range)
    print("Query", start, end)
