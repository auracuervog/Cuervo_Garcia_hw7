import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import sys

filename = sys.argv[1]
newfilename = filename[0:11]
datos = np.loadtxt(filename)
z = datos;
print z.shape

nt, nx = 101, 1201
X = range(nt)
Y = range(nx)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

X, Y = np.meshgrid(X, Y) 
ax.plot_surface(X, Y, z)
ax.set_xlabel('t(s)')
ax.set_ylabel('x(m)')
ax.set_zlabel('y(m)')

plt.savefig(newfilename + '.pdf',format = 'pdf', transparent=True)
plt.show()
