#!/usr/bin/env python3
import re
import matplotlib.pyplot as plt
from pathlib import Path
from matplotlib.lines import Line2D
import matplotlib.patches as mpatches
from matplotlib.figure import figaspect

nodes = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000]
degrees = [0.01]
weights = [1000]

text = Path("mst-size-sparse.bench").read_text()
lines = [line for line in text.splitlines()][3:]
searches = [re.search("BM_(.*)/(\d+)/(\d+)/(\d+) *(\d+) *.*", l) for l in lines]
groups = [s.groups() for s in searches if s]

values = dict()
for (name, n,d,w,t) in groups:
    if name not in values: values[name] = []
    values[name].append((nodes[int(n)], degrees[int(d)], weights[int(w)], int(t)))

# x = degree, y = time
fig, ax = plt.subplots(figsize=(10,5))

def add(name, degree, color, linestyle):
    x = [v[0] for v in values[name] if v[1] == degree]
    y = [v[3] for v in values[name] if v[1] == degree]
    ax.plot(x, y, color=color, linestyle=linestyle)


add('Kruskal',         0.01, "brown", "-.")
add('KruskalCounting', 0.01, "black", "-.")

add('Kruskal2Heap',    0.01, "red", ":")
add('KruskalD8Heap',   0.01, "blue", ":")
add('KruskalD16Heap',  0.01, "green", ":")
#add('KruskalD32Heap',  0.01, "k", ":")
add('KruskalD64Heap',  0.01, "purple", ":")
#add('KruskalFHeap',    0.01, "k", ":")

add('Prim2Heap',   0.01, "red", "-")
add('PrimD8Heap',  0.01, "blue", "-")
add('PrimD16Heap', 0.01, "green", "-")
#add('PrimD32Heap', 0.01, "k", "-")
add('PrimD64Heap', 0.01, "purple", "-")
#add('PrimFHeap',   0.01, "k", "-")

#add('Edmonds2Heap',   0.01, "k", "--")
#add('EdmondsD8Heap',  0.01, "k", "--")
#add('EdmondsD16Heap', 0.01, "k", "--")
#add('EdmondsD32Heap', 0.01, "k", "--")
#add('EdmondsD64Heap', 0.01, "k", "--")
#add('EdmondsFHeap',   0.01, "k", "--")


kruskal_stdsort = Line2D([0], [0], label='krusal stdsort',  color='brown', linestyle='-.')
kruskal_cntsort = Line2D([0], [0], label='krusal cntsort',  color='black', linestyle='-.')

kruskal_d2heap = Line2D([0], [0], label='kruskal 2-heap',  color='red', linestyle=':')
kruskal_d8heap = Line2D([0], [0],  label='kruskal 8-heap', color='blue', linestyle=':')
kruskal_d16heap = Line2D([0], [0],  label='kruskal 16-heap', color='green', linestyle=':')
kruskal_d64heap = Line2D([0], [0],  label='kruskal 64-heap', color='purple', linestyle=':')

prim_d2heap = Line2D([0], [0], label='prim 2-heap',  color='red', linestyle='-')
prim_d8heap = Line2D([0], [0],  label='prim 8-heap', color='blue', linestyle='-')
prim_d16heap = Line2D([0], [0],  label='prim 16-heap', color='green', linestyle='-')
prim_d64heap = Line2D([0], [0],  label='prim 64-heap', color='purple', linestyle='-')

dummy = Line2D([0],[0],color="w")

ax.legend(handles=[
    prim_d2heap, prim_d8heap, prim_d16heap, prim_d64heap,
    kruskal_d2heap, kruskal_d8heap, kruskal_d16heap, kruskal_d64heap,
    kruskal_stdsort, kruskal_cntsort, dummy, dummy
], ncol=3)


ax.axis([0, 9010, 1*10**4, 1*10**8])
ax.set_xticks([100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000])
plt.yscale("log", base=10)

plt.xlabel("Nodes")
plt.ylabel("Time [ns]")

#plt.show()
plt.savefig('mst-size-sparse.png', bbox_inches='tight')
