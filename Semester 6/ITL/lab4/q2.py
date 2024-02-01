class Q2:
    array=[]
    result=[]
    def __init__(self,array,target):
        self.array=array
        self.target=target
        self.result=[]

    def find(self):
        for i in range(len(array)):
            for j in range(i+1,len(array)):
                if array[i]+array[j]== self.target:
                    self.result.append(i)
                    self.result.append(j)
                    return self.result


        return -1
                
array = [ int(x) for x in input('Enter distinct elements of array: ').split() ]
target=int(input("Enter target number"))
q2=Q2(array,target)
print(q2.find())