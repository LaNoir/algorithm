T = int(input())

a = list(map(int,input().split()))

max_val = -1000001
min_val = 1000001
for x in a:
    max_val = max(max_val, x)
    min_val = min(min_val, x)

print("{0} {1}".format(min_val,max_val))
