#!/usr/bin/env python3
import re
import matplotlib.pyplot as plt
from pathlib import Path
from matplotlib.lines import Line2D
import matplotlib.patches as mpatches
from matplotlib.figure import figaspect

nodes = [500]
degrees = [1.0]
weights = [1000]

text = Path("msa-variation.bench").read_text() 
lines = [line for line in text.splitlines()][3:]
searches = [re.search("BM_(.*)/(\d+)/(\d+)/(\d+) *(\d+) *.*", l) for l in lines]
groups = [s.groups() for s in searches if s]

values = dict()
for (name, n,d,w,t) in groups:
    if name not in values: values[name] = []
    values[name].append((nodes[int(n)], degrees[int(d)], weights[int(w)], int(t)))

fig, ax = plt.subplots(figsize=(10,5))

vals, names = [], []
def add(name, nodes, label):
    #x = [v[1] for v in values[name] if v[0] == nodes]
    y = [v[3] for v in values[name] if v[0] == nodes and v[1] == 1.0]
    #ax.scatter(x, y, c=color, marker=linestyle)
    #ax.plot(x, y, color=color, linestyle=linestyle)
    vals.append(y)
    names.append(label)


add('Edmonds2Heap',   500, "edmonds 2-heap")
add('EdmondsD8Heap',  500, "edmonds 8-heap")
add('EdmondsD16Heap', 500, "edmonds 16-heap")
add('EdmondsD64Heap', 500, "edmonds 64-heap")

add('EdmondsFHeap',   500, "edmonds f-heap")
ax.boxplot(vals, labels=names)

#ax.axis([0.0, 1.01, 7*10**4, 2*10**9])
plt.yscale("log", base=10)

plt.ylabel("Time [ns]")

#plt.show()
plt.savefig('msa-variation.png', bbox_inches='tight')
