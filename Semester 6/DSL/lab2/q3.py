import pandas as pd 
import numpy as np 

data={
    'Name': ['Ram','Shyam','Madhav','Madhu'],
    'Height': [180,170,160,150],
    'Qualification': ['BTech','MTech','MSc','Phd']
}

df=pd.DataFrame(data)
print(df)

add=['mumbai','hyderabad','delhi','bangalore']
df['address']=add
print(df)

df.insert(1,'Age',[21,24,25,30])
print(df)