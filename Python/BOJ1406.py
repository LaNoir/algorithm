from sys import stdin

left = list(input())
right = []

T = int(input())

while T:
    T-=1
    command = stdin.readline().strip().split()

    if(command[0] == 'L'):
        if(len(left)):
            right.append(left.pop())
    elif(command[0] == 'D'):
        if(len(right)):
            left.append(right.pop())
    elif(command[0] == 'B'):
        if(len(left)):
            left.pop()
    elif(command[0] == 'P'):
        left.append(command[1])

s = left

while (len(right)):
    s.append(right.pop())

a = ""
for x in s:
    a+=x

print(a)