a=int(input("Enter 1st number: "))
b=int(input("Enter 2nd number: "))
op=input("Enter operator")

if op=='+':
    print("Result: ",a+b)

elif op=='-':
    print("result: ",a-b)

elif op=='*':
    print("result: ",a*b)

elif op=='/':
    print("result: ",a/b)

else:
    print("Invalid");
