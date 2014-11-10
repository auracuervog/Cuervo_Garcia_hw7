import sys
import matplotlib.pyplot as plt
import numpy as np


entrada=sys.argv[1]

entrada1=entrada.split(".")

data=np.loadtxt(entrada)



f, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2)
ax1.plot(data[:,0], data[:,1])
ax1.set_title('Sharing x per column, y per row')
ax2.plot(data[:,0], data[:,2])
ax3.plot(data[:,0], data[:,3])

plt.savefig(entrada1[0]+"."+entrada1[1]+".pdf")
