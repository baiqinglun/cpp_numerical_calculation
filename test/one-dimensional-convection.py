import numpy as np
import matplotlib.pyplot as plt

nx = 41#空间网格数
dx = 2/(nx-1)#空间网格尺寸
nt=20#时间步数
dt=0.025#时间步长

u = np.ones (nx)
u[int(0.6/dx):int(1/dx+1)]=2
u_init = u.copy()
plt.ion()
plt.show()
un  = np.ones (nx)
for n in range(nt):
    plt.cla()
    plt.plot(np.linspace(0,2,nx),u_init,'g--',lw=3,label='init')
    un = u.copy()
    for i in range (1,nx):
        u[i] = un[i]-un[i]*dt/dx*(un[i]-un[i-1])
    plt.plot(np.linspace(0,2,nx),u,'r',lw=3,label='current')
    plt.legend()
    plt.pause(.2)
plt.ioff()
plt.show()