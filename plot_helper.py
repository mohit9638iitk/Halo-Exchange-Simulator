
# coding: utf-8




# In[3]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sys


# In[18]:


Input=sys.argv[1]


# In[73]:


df=pd.read_csv(Input,names=['Y'])


# In[74]:


df.head()


# In[75]:


temp=np.array(df['Y'])


# In[76]:


len(temp)


# In[77]:


import math


# In[78]:


method1=[]
method2=[]
method3=[]
for i in range(0,len(temp),3):
    method1.append(math.log2(temp[i]))
    method2.append(math.log2(temp[i+1]))
    method3.append(math.log2(temp[i+2]))


# In[79]:


len(method1)


# In[80]:


y1=[]
y2=[]
y3=[]


# In[81]:


for i in range(0,7):
    t1=[]
    t2=[]
    t3=[]
    for j in range(i,len(method2),7):
        t1.append(method1[j])
        t2.append(method2[j])
        t3.append(method3[j])
    y1.append(t1)
    y2.append(t2)
    y3.append(t3)


# In[82]:


len(y1)


# In[83]:


y1


# In[84]:


name=Input.split(".")[0]




# In[122]:


def plot_fcn(y1,y2,y3):
    x=['16^2','32^2','64^2','128^2','256^2','512^2','1024^2']
    plt.figure(figsize=(10,10), dpi=108)
    
    red_diamond = dict(markerfacecolor='r', marker='D')
    plt.boxplot(y1, labels=x,medianprops={'color': 'r'},flierprops=red_diamond,showmeans=False)
    blue_diamond = dict(markerfacecolor='b', marker='D')
    plt.boxplot(y2, labels=x,medianprops={'color': 'b'},flierprops=blue_diamond,showmeans=False)
    green_diamond = dict(markerfacecolor='g', marker='D')
    plt.boxplot(y3, labels=x,medianprops={'color': 'g'},flierprops=green_diamond,showmeans=False)
    
    temp=np.array([np.median(j) for j in y1])
    plt.plot(range(1,8), temp, label="Multiple MPI_Sends",color = 'r')
    temp=np.array([np.median(j) for j in y2])
    plt.plot(range(1,8), temp, label="MPI_Pack",color = 'b')
    temp=np.array([np.median(j) for j in y3])
    plt.plot(range(1,8), temp, label="MPI derived datatype",color = 'g')
    
    
    plt.xlabel("Size of data matrix")
    plt.ylabel("Time in sec(log2 scale)")
    plt.title("Box Plot for P="+name[4:6]+" processes")
    plt.legend()
    plt.savefig(name+".jpg")
    


# In[123]:


plot_fcn(y1,y2,y3)

