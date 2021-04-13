from sys import stdin

while(1):
    stack = []
    flag = True
    
    t = stdin.readline().rstrip()
    if(t=='.'):
        break
    
    for x in t:
        if(x=='(' or x=='['):
            stack.append(x)
        elif(x == ')'):
            if(len(stack)==0):
                flag=False
                break
            temp = stack[-1] 
            if(temp != '('):
                flag=False
                break
            stack.pop()
        elif(x == ']'):
            if(len(stack)==0):
                flag=False
                break
            temp = stack[-1] 
            if(temp != '['):
                flag=False
                break
            stack.pop()
    
    if(len(stack)!=0):
        flag=False
    if(flag == False):
        print("no")
    else:
        print("yes")
