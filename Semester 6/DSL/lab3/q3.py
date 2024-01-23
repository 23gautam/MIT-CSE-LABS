import numpy as np 
import random

list1=[1.2,2.4,3.5,5.3,9.3]
a=np.array(list1)
print(a)
print(a.dtype)


list2= (1,5,3,2,8)
b=np.array(list2)
print(b)

c=np.zeros((3,4))
print(c)

d=np.array(np.arange(0,20,5))
print(d)

e=c.reshape(2,2,3)
print(e)

f=np.array(random.sample(range(10,30),4)).reshape(2,2)
print(f)
print("Row max: ",f.max(axis=1))
print("Row min: ",f.min(axis=1))
print("Col max: ",f.max(axis=0))
print("Col min: ",f.min(axis=0))

print("Max: ",f.max())
print("Min: ",f.min())
print("Sum: ",f.sum())

