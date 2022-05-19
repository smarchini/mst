#!/usr/bin/env python3
import re
import matplotlib.pyplot as plt
from pathlib import Path
from matplotlib.lines import Line2D
import matplotlib.patches as mpatches
from matplotlib.figure import figaspect

nodes = [500]
degrees = [0.01, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
weights = [1000]

text = Path("msa-density-median50.bench").read_text()
lines = [line for line in text.splitlines()][3:]
searches = [re.search("BM_(.*)/(\d+)/(\d+)/(\d+) *(\d+) *.*", l) for l in lines]
groups = [s.groups() for s in searches if s]

values = dict()
for (name, n,d,w,t) in groups:
    if name not in values: values[name] = []
    values[name].append((nodes[int(n)], degrees[int(d)], weights[int(w)], int(t)))

fig, ax = plt.subplots(figsize=(10,5))

def add(name, nodes, color, linestyle):
    x = [v[1] for v in values[name] if v[0] == nodes]
    y = [v[3] for v in values[name] if v[0] == nodes]
    #ax.scatter(x, y, c=color, marker=linestyle)
    ax.plot(x, y, color=color, linestyle=linestyle)


add('Edmonds2Heap',   500, "red", "-")
add('EdmondsD8Heap',  500, "blue", "-")
add('EdmondsD16Heap', 500, "green", "-")
add('EdmondsD64Heap', 500, "purple", "-")

add('EdmondsFHeap',   500, "black", ":")

edmonds_d2heap = Line2D([0], [0], label='edmonds 2-heap', color='red', linestyle='-')
edmonds_d8heap = Line2D([0], [0], label='edmonds 8-heap', color='blue', linestyle='-')
edmonds_d16heap = Line2D([0], [0], label='edmonds 16-heap', color='green', linestyle='-')
edmonds_d64heap = Line2D([0], [0], label='edmonds 64-heap', color='purple', linestyle='-')

edmonds_fheap = Line2D([0], [0], label='edmonds f-heap', color='black', linestyle=':')

dummy = Line2D([0],[0],color="w")

ax.legend(handles=[
    edmonds_d2heap, edmonds_d8heap, edmonds_d16heap, edmonds_d64heap,
    edmonds_fheap, dummy, dummy, dummy
], ncol=2)

ax.axis([0.0, 1.01, 7*10**4, 2*10**9])
ax.set_xticks([0.01, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0])
plt.yscale("log", base=10)

plt.xlabel("Density")
plt.ylabel("Time [ns]")

#plt.show()
plt.savefig('msa-density-median50.png', bbox_inches='tight')
