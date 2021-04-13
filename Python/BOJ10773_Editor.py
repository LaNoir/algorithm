from sys import stdin

k = int(input())
stack=[]
while k:
    k-=1
    a = int(stdin.readline().strip())
    if(a!=0):
        stack.append(a)
    else:
        stack.pop()

t =0
for x in stack:
    t+=x
print(t)