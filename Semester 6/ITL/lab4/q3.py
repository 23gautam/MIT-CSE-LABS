class Q3:
    
    def __init__(self,x,n):
        self.x=x
        self.n=n

    def pow(self):
        result=1
        for i in range(n):
            result*=x
        
        return result
    
x=int(input("Enter x: "))
n=int(input("Enter n: "))
q3=Q3(x,n)
print(q3.pow())