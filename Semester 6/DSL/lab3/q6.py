import numpy as np
import random

a=np.array(random.sample(range(10),4)).reshape(2,2)
b=np.array(random.sample(range(10),4)).reshape(2,2)

print(a)
print(b)
print(a*b)