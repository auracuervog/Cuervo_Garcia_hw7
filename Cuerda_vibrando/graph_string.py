import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import sys

filename = sys.argv[1]
datos = np.loadtxt(filename)
y = datos;

t = []
x = []

for i in range(0,121):
    t.append(i)
for j in range(0,101):
    x.append(j)    

fig=plt.figure()
ax = fig.add_subplot(111, projection='3d')
fi = fig.gca(projection='3d')
fi.scatter(x,t,y)
fi.set_xlabel('x(m)')
fi.set_ylabel('t(s)')
fi.set_zlabel('y(m)')

plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.show() 
