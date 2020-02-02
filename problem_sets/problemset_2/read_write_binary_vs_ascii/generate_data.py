import numpy as np
n = 1000000
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


temperatures = [str(i*0.1) for i in range(n)];
time = [str(i) for i in range(n)];
binary_temps = [bytes(temp, "utf-8") for temp in temperatures];
binary_time = [bytes(t, "utf-8") for t in time];


with open("temperatures_binary.bin", "wb") as outfile:
    for t, temp in zip(binary_time, binary_temps):
        outfile.write(t)
        outfile.write(bytes(" ", "utf-8"))
        outfile.write(temp)
        outfile.write(bytes("\n","utf-8"))



"""
mean = np.mean(temperatures)
std = np.std(temperatures)
min_val = min(temperatures)
max_val = max(temperatures)

print(mean)
print(std)
print(min_val)
print(max_val)
"""
