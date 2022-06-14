#!/usr/bin/env python3
import re
import matplotlib.pyplot as plt
from pathlib import Path
from matplotlib.lines import Line2D
import matplotlib.patches as mpatches
from matplotlib.figure import figaspect

nodes = [10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
degrees = [1.00]
weights = [1000]

text = Path("msa-size-median50.bench").read_text()
lines = [line for line in text.splitlines()][3:]
searches = [re.search("BM_(.*)/(\d+)/(\d+)/(\d+) *(\d+) *.*", l) for l in lines]
groups = [s.groups() for s in searches if s]

values = dict()
for (name, n,d,w,t) in groups:
    if name not in values: values[name] = []
    values[name].append((nodes[int(n)], degrees[int(d)], weights[int(w)], int(t)))

fig, ax = plt.subplots(figsize=(10,5))

def add(name, degree, color, linestyle):
    x = [v[0] for v in values[name] if v[1] == degree]
    y = [v[3] for v in values[name] if v[1] == degree]
    #ax.scatter(x, y, c=color, marker=linestyle)
    ax.plot(x, y, color=color, linestyle=linestyle)


add('Edmonds2Heap',   1.00, "red", "-")
add('EdmondsD8Heap',  1.00, "blue", "-")
add('EdmondsD16Heap', 1.00, "green", "-")
add('EdmondsD64Heap', 1.00, "purple", "-")

add('EdmondsFHeap',   1.00, "black", ":")

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


ax.axis([0, 1010, 1*10**3, 1*10**10])
ax.set_xticks([10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000])
plt.yscale("log", base=10)

plt.xlabel("Nodes")
plt.ylabel("Time [ns]")

#plt.show()
plt.savefig('msa-size-median50.pdf', bbox_inches='tight')
