import numpy as np
import matplotlib.pyplot as plt

nx = 1000
dx = 2/(nx-1)
nt = 20
c = 1
sigma = 0.5
dt = sigma * dx
u = np.ones(nx)
u[int(0.5/dx) : int(1/dx+1)] = 2
plt.plot(np.linspace (0,2,nx),u,'b',lw=3,label='origin')
un=np.ones (nx)
for n in range(nt):
    un = u.copy()
    for i in range(1,nx):
        u[i] = un[i]-c*dt/dx*(un[i]-un[i-1])
plt.plot(np.linspace(0,2,nx),u,'r',lw=3,label='current')
plt.legend()
plt.show()