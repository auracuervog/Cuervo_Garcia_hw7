import sys
import matplotlib.pyplot as plt
import numpy as np


entrada=sys.argv[1]
entrada1=entrada.split(".")
data=np.loadtxt(entrada)


ax1 = plt.subplot(311)
plt.plot(data[:,0], data[:,1])

ax1.set_title('Sharing x per column, y per row')

ax2 = plt.subplot(312, sharex=ax1)
ax2.plot(data[:,0], data[:,2])

ax3 = plt.subplot(313, sharex=ax1)
ax3.plot(data[:,0], data[:,3])

plt.savefig(entrada1[0]+"."+entrada1[1]+".pdf")
