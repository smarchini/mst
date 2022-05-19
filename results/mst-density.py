#!/usr/bin/env python3
import re
import matplotlib.pyplot as plt
from pathlib import Path
from matplotlib.lines import Line2D
import matplotlib.patches as mpatches
from matplotlib.figure import figaspect

nodes = [500]
degrees = [0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
weights = [1000]

text = Path("mst-density.bench").read_text()
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
    ax.plot(x, y, color=color, linestyle=linestyle)


add('Kruskal',         500, "brown", "-.")
add('KruskalCounting', 500, "black", "-.")

add('Kruskal2Heap',    500, "red", ":")
add('KruskalD8Heap',   500, "blue", ":")
add('KruskalD16Heap',  500, "green", ":")
#add('KruskalFHeap',    500, "pink", ":")

add('Prim2Heap',   500, "red", "-")
add('PrimD8Heap',  500, "blue", "-")
add('PrimD16Heap', 500, "green", "-")
#add('PrimFHeap',   500, "pink", "-")

# add('Edmonds2Heap',   500, "k", "--")
# add('EdmondsD8Heap',  500, "k", "--")
# add('EdmondsD16Heap', 500, "k", "--")
# add('EdmondsFHeap',   500, "k", "--")


kruskal_stdsort = Line2D([0], [0], label='krusal stdsort',  color='brown', linestyle='-.')
kruskal_cntsort = Line2D([0], [0], label='krusal cntsort',  color='black', linestyle='-.')

kruskal_d2heap = Line2D([0], [0], label='kruskal 2-heap',  color='red', linestyle=':')
kruskal_d8heap = Line2D([0], [0],  label='kruskal 8-heap', color='blue', linestyle=':')
kruskal_d16heap = Line2D([0], [0],  label='kruskal 16-heap', color='green', linestyle=':')

prim_d2heap = Line2D([0], [0], label='prim 2-heap',  color='red', linestyle='-')
prim_d8heap = Line2D([0], [0],  label='prim 8-heap', color='blue', linestyle='-')
prim_d16heap = Line2D([0], [0],  label='prim 16-heap', color='green', linestyle='-')

ax.legend(handles=[
    prim_d2heap, prim_d8heap, prim_d16heap,
    kruskal_d2heap, kruskal_d8heap, kruskal_d16heap,
    kruskal_stdsort, kruskal_cntsort
], ncol=3)

ax.axis([0.0, 1.01, 3*10**4, 2*10**7])
ax.set_xticks([0.01, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0])
plt.yscale("log", base=10)

plt.xlabel("Density")
plt.ylabel("Time [ns]")

#plt.show()
plt.savefig('mst-density.png', bbox_inches='tight')
