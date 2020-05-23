import numpy as np
from time import time

n = 5000;
A = np.random.normal(0, 1, size = (n,n))
b = np.random.normal(0,1, size = n)
y = np.random.normal(0, 1, size = n)

start = time()
y = np.linalg.solve(A,b)
end = time()
timeused = end-start
print("Time used = ", timeused)
