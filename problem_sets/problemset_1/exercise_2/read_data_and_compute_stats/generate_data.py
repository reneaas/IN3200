import numpy as np
n = 100
time = np.array([i for i in range(n)])

temperatures = np.array([i*0.1 for i in range(n)])
shuffled_indices = np.random.permutation(n)
temperatures = temperatures[shuffled_indices];

print(temperatures)


outfilename = "temperatures.txt"
with open(outfilename, "w") as outfile:
    for i in range(n):
        outfile.write(str(time[i]) + " " + str(temperatures[i]) + "\n")
        #outfile.write(str(temperatures[i]) + "\n")

mean = np.mean(temperatures)
std = np.std(temperatures)
min_val = min(temperatures)
max_val = max(temperatures)

print(mean)
print(std)
print(min_val)
print(max_val)
