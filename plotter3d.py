import numpy as np
import csv
import os
#%matplotlib
import matplotlib.pyplot as plt
import mpl_toolkits
from mpl_toolkits.mplot3d import Axes3D
from pylab import *

path = input("Enter the path of the folder containing the files for plotting: ")
zlen = float(input("Enter the length of the object (it's size in z-direction): "))
xlen = float(input("Enter the width of the object (it's size in x-direction): "))
ylen = float(input("Enter the height of the object (size in y-direction): "))
res = float(input("Enter the resolution of the measurmement system (it's step size): "))
elevel = float(input("Enter the energy level of the current data set: "))

#xseg = np.arange(0.01,0.1,0.01)
#x = np.empty((22,9))
#y = np.empty((22,9))
#z = np.empty(())
#for j in range(1,22):
#    yseg = np.full((1,9), j*0.01)
#    y[j-1] = yseg
#    x[j-1] = xseg
x = np.arange(0,xlen, res)
xarr = []
print(size(x))
y = np.arange(0,ylen, res)
print(size(y))
z = np.arange(0,zlen, res)
print(size(z))
    
coloarr = []
filelist = os.scandir(path)
i=0
for entry in filelist:
    xmat = []
    ymat = []
    zmat = []
    if entry.is_file():
        print(entry)
        with open(entry, 'r') as fname:
            reader = csv.reader(fname)
            data = list(reader)
        temparr = np.array(data, dtype=float)
        for j in range(0,len(temparr)):
            x = np.arange(res,(len(temparr[0])+1)*res,res)
            y = np.full(len(x),(j+1)*res)
            z = np.full(len(x), (i+1)*res)
            xmat.append(x)
            ymat.append(y)
            zmat.append(z)
        if (i == 0):
            temparr0 = temparr
            xarr0 = xmat
            yarr0 = ymat
            zarr0 = zmat
            #coloarr = temparr.reshape((len(temparr),len(temparr[1]),1))
        if (i == 1):
            coloarr = np.stack((temparr0, temparr))
            xarr = np.stack((xarr0, xmat))
            yarr = np.stack((yarr0, ymat))
            zarr = np.stack((zarr0, zmat))
        if (i > 1):
            np.array([temparr]).shape
            (1, len(temparr), len(temparr[0]))
            coloarr = np.concatenate((coloarr, [temparr]))
            np.array([xmat]).shape
            (1, len(xmat), len(xmat[0]))
            xarr = np.concatenate((xarr, [xmat]))
            np.array([ymat]).shape
            (1, len(ymat), len(ymat[0]))
            yarr = np.concatenate((yarr, [ymat]))
            np.array([zmat]).shape
            (1, len(zmat), len(zmat[0]))
            zarr = np.concatenate((zarr, [zmat]))
        i+=1
        #coloarr = np.loadtxt(entry, delimiter=",", dtype=float)
 

# creating figures 

fig = plt.figure(figsize=(11, 11)) 
ax = fig.add_subplot(111, projection='3d') 
  
# setting color bar 
color_map = cm.ScalarMappable(cmap=cm.coolwarm) 
color_map.set_array(coloarr) 
  
# creating the heatmap 
#change color for heatmap
img = ax.scatter(xarr, yarr, zarr, c=coloarr, s=500, cmap='coolwarm') 
#plt.colorbar(color_map) 
  
# adding title and labels 
ax.set_title("Neutron Heatmap: " + str(elevel) + " eV") 
ax.set_xlabel('X-axis') 
ax.set_ylabel('Y-axis') 
ax.set_zlabel('Z-axis') 
  
# displaying plot 
plt.show() 

# #For looking into follow-on imaging plate results, look at the sensitivity on the m
# #manufacturing website - tech sheets
# #look into noise level that might be present and signal lvl
