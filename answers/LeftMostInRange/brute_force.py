def find_min_x(y1, y2, points):
    min_x = 210000000000
    for point in points:
        if y1 <= point[1] <= y2:
            min_x = min(min_x, point[0])
    if min_x == 210000000000:
        return "No Data"
    return min_x


n = int(input())

points = []
for i in range(n):
    line = input()
    elements = line.split(" ")
    op = elements[0]
    num1 = int(elements[1])
    num2 = int(elements[2])
    if op == "Insert":
        points.append([num1, num2])
    elif op == "Query":
        print(find_min_x(num1, num2, points))