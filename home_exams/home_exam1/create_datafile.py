import numpy as np


outfilename = "test_webpages.txt"

nodes = 1000;
edges = 1000;
np.random.seed(1001)
#numbers1 = np.random.randint(nodes, size = edges)
numbers1 = [i for i in range(nodes)]*2
numbers1 = np.array(numbers1)
numbers1 = numbers1[np.random.permutation(nodes*2)]
#np.random.seed(1000)
numbers2 = np.array([i for i in range(nodes)]*2)
numbers2 = numbers2[np.random.permutation(nodes*2)]

print(numbers1[0])
print(numbers2[0])

with open(outfilename, "w") as outfile:
    outfile.write("# Directed graph (each unordered pair of nodes is saved once): " + outfilename + "\n")
    outfile.write("# Just an example\n")
    outfile.write("# Nodes: " + str(nodes) + " Edges: " + str(edges) + "\n")
    outfile.write("# FromNodeId    ToNodeId\n")
    for i, j in zip(numbers1, numbers2):
        outfile.write(str(i) + " " + str(j) + "\n")
