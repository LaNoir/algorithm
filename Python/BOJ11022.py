T = int(input())
count = 1
while(count<= T):
    a,b = map(int,input().split())
    print("Case #{0}: {1} + {2} = {3}".format(count, a,b, a+b))
    count += 1
