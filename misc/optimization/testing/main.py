import numpy as np

A = np.array([[0,6,8], [12,0,4], [6,6,0]])

A_inv = np.linalg.inv(A)
print(A_inv)
