import pandas as pd

data1={
    'Name': ['Ram','Diya','Chandan','James','Alice']
}
df1=pd.DataFrame(data1)

data2={
    'Maths': [80,90,77.5,87.5,86.5],
    'Physics': [81,94,74.5,83,82.5],
    'Chemistry': [91.5,86.5,85.5,90,91],
    'Biology': [82.5,83.5,84.5,85,93]
}

df2=pd.DataFrame(data2)
print(df1,"\n",df2)

df_new=pd.concat([df1,df2],axis=1)
print(df_new)


df_new['Total']=df2.sum(axis=1)
print(df_new)


