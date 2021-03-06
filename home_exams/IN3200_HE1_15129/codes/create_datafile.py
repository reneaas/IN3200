"""
This script reads web-NotreDame.txt and extracts all viable (FromNodeId, ToNodeId)-pairs
that does not exceed the maximum allowed index value nodes-1. This code is written
with the intent to create a medium large webgraph to be used with
the hyperlink matrix representation used in part 1 of the home exam.
"""

import numpy as np


infilename = "web-NotreDame.txt"
N = int(input("Give number of nodes = "))
nodes = N-1;

FromNodeId = []
ToNodeId = []
with open(infilename, "r") as infile:
    infile.readline()
    infile.readline()
    infile.readline()
    infile.readline()
    lines = infile.readlines()
    for line in lines:
        vals = line.split()
        FromNodeId.append(int(vals[0]))
        ToNodeId.append(int(vals[-1]))

FromNodeId = np.array(FromNodeId)
ToNodeId = np.array(ToNodeId)


#Check where values are too large in FromNodeId and remove them.
indices1 = np.where(FromNodeId > nodes)
FromNodeId[indices1] = -1
ToNodeId[indices1] = -1

#Check where values are too large in ToNodeId and remove them.
indices2 = np.where(ToNodeId > nodes)
FromNodeId[indices2] = -1
ToNodeId[indices2] = -1


#Fill lists with the actual node id pairs we want:
numbers1 = []
numbers2 = []
for i in range(len(FromNodeId)):
    if FromNodeId[i] != -1:
        numbers1.append(FromNodeId[i])
        numbers2.append(ToNodeId[i])

nodes = N
edges = len(numbers1)
print("Nodes = ", nodes)
print("Edges = ", edges)

outfilename = "test_webpages.txt"
with open(outfilename, "w") as outfile:
    outfile.write("# Directed graph (each unordered pair of nodes is saved once): " + outfilename + "\n")
    outfile.write("# Just an example\n")
    outfile.write("# Nodes: " + str(nodes) + " Edges: " + str(edges) + "\n")
    outfile.write("# FromNodeId    ToNodeId\n")
    for i, j in zip(numbers1, numbers2):
        outfile.write(str(i) + " " + str(j) + "\n")
