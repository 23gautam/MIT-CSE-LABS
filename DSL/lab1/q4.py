a=float(input('Enter val1: '))
b=float(input('Enter val2: '))
c=float(input('Enter val3: '))

if a>b and a>c:
	print("A largest")
elif b>a and b>c:
	print("B largest")
elif c>a and c>b:
	print("C largest")