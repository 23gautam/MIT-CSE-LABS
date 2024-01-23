import numpy as np 
import random

a=np.array(random.sample(range(10,30),4)).reshape(2,2)
print(a)
print("Col sum: ",a.sum(axis=0))
print("Row Sum: ",a.sum(axis=1))