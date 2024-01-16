import pandas as pd 
import numpy as np 
import matplotlib.pyplot

B=pd.read_html('http://www.fdic.gov/bank/individual/failed/banklist.html',header=None)
print(B.head())