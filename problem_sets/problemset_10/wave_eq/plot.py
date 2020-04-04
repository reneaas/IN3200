import matplotlib.pyplot as plt
import numpy as np


infilename = "results.txt"
u = []

with open(infilename, "r") as infile:
    for line in infile:
        vals = line.split()
        u.append(float(vals[0]))


n = len(u)
x = np.linspace(0,1,n)

plt.plot(x,u)
plt.xlabel("x")
plt.ylabel("u(x)")
plt.show()
