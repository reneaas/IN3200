import numpy as np
import matplotlib.pyplot as plt
import os

if not os.path.exists("results/"):
    os.makedirs("results/")


os.system("rm results/count_mutual_links1_parallel_results.txt")
os.system("rm results/count_mutual_links2_parallel_results.txt")

os.system("mv count_mutual_links1_parallel_results.txt results/")
os.system("mv count_mutual_links2_parallel_results.txt results/")


filename1 = "results/count_mutual_links1_parallel_results.txt"
filename2 = "results/count_mutual_links2_parallel_results.txt"

timeused1 = []
timeused2 = []
threads1 = []
threads2 = []

with open(filename1, "r") as infile:
    infile.readline()
    lines = infile.readlines()
    for line in lines:
        vals = line.split()
        timeused1.append(float(vals[0]))
        threads1.append(float(vals[-1]))


with open(filename2, "r") as infile:
    infile.readline()
    lines = infile.readlines()
    for line in lines:
        vals = line.split()
        timeused2.append(float(vals[0]))
        threads2.append(float(vals[-1]))


timeused1 = np.array(timeused1)
timeused2 = np.array(timeused2)
threads1 = np.array(threads1)
threads1 = np.log2(threads1)
threads2 = np.array(threads2)
threads2 = np.log2(threads2)



filenames = ["count_mutual_links1_parallel.pdf", "count_mutual_links2_parallel.pdf", "count_mutual_links1_speedup.pdf", "count_mutual_links2_speedup.pdf"]
plt.figure()
plt.plot(threads1, timeused1)
plt.scatter(threads1,timeused1, color = "r")
plt.xlabel("log2(threads)", size = 14)
plt.ylabel("Time [s]", size = 14)
plt.xticks(size = 14)
plt.yticks(size = 14)
plt.savefig(filenames[0])
plt.close()

plt.figure()
plt.plot(threads2, 1000*timeused2)
plt.scatter(threads2, 1000*timeused2, color = "r")
plt.xlabel("log2(threads)", size = 14)
plt.ylabel("Time [ms]", size = 14)
plt.xticks(size = 14)
plt.yticks(size = 14)
plt.savefig(filenames[1])
plt.close()

plt.figure()
plt.plot(threads1, timeused1[0]/timeused1)
plt.scatter(threads1,timeused1[0]/timeused1, color = "r")
plt.xlabel("log2(threads)", size = 14)
plt.ylabel("Speedup", size = 14)
plt.xticks(size = 14)
plt.yticks(size = 14)
plt.savefig(filenames[2])
plt.close()

plt.figure()
plt.plot(threads2, timeused2[0]/timeused2)
plt.scatter(threads2, timeused2[0]/timeused2, color = "r")
plt.xlabel("log2(threads)", size = 14)
plt.ylabel("Speedup", size = 14)
plt.xticks(size = 14)
plt.yticks(size = 14)
plt.savefig(filenames[3])
plt.close()

filenames = ["count_mutual_links1_parallel.pdf", "count_mutual_links2_parallel.pdf", "count_mutual_links1_speedup.pdf", "count_mutual_links2_speedup.pdf"]
target_directory = "/home/reneaas/Documents/skole/IN3200/home_exams/home_exam1/report"
for filename in filenames:
    os.system("mv" + " " + filename + " " + target_directory)
