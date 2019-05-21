import sys
import matplotlib.pyplot as plt

plt.plotfile(sys.argv[1],cols=(0,1),names=["Numero de Paginas","Tempo"],delimiter=" ")
plt.show()
