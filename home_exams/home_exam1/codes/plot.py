import numpy as np
import matplotlib.pyplot as plt

filename1 = "results/count_mutual_links1_parallel_results.txt"
filename2 = "results/count_mutual_links2_parallel_results.txt"

timeused1 = []
timeused2 = []
threads = []

with open(filename1, "r") as infile:
    infile.readline()
    lines = infile.readlines()
    for line in lines:
        vals = line.split()
        timeused1.append(float(vals[0]))
        threads.append(float(vals[-1]))


with open(filename2, "r") as infile:
    infile.readline()
    lines = infile.readlines()
    for line in lines:
        vals = line.split()
        timeused2.append(float(vals[0]))


timeused1 = np.array(timeused1)
timeused2 = np.array(timeused2)
threads = np.array(threads)
threads = np.log2(threads)

plt.figure()
plt.plot(threads, timeused1)
plt.scatter(threads,timeused1, color = "r")
plt.xlabel("log2(threads)")
plt.ylabel("timeused [s]")
plt.savefig("count_mutual_links1_parallel.pdf")
plt.close()

plt.figure()
plt.plot(threads, timeused2)
plt.scatter(threads,timeused2, color = "r")
plt.xlabel("log2(threads)")
plt.ylabel("timeused [s]")
plt.savefig("count_mutual_links2_parallel.pdf")
plt.close()
