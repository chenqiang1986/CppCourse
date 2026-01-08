def count(points, row_start, row_end, col_start, col_end):
    counter = 0
    for point in points:
        if row_start <= point[0] <= row_end and col_start <= point[1] <= col_end:
            counter += 1
    return counter

n = int(input())
points = []
for i in range(n):
    action_whole = input()
    split_action = action_whole.split(" ")
    if split_action[0] == "Input":
        points.append([split_action[1], split_action[2]])
    else:
        print(count(points, split_action[1], split_action[2], split_action[3], split_action[4]))