# Experimental Evaluation of MST Algorithms
Experimental analysis on the impact of different algorithms and heap-based data
structures for the minimal spanning tree problem in directed and undirected
graphs. The goal is to identify strengths and weaknesses of various approaches
in order to guide application programmers towards the best choice for their
specific applications. The study is conducted on random graphs of various size
and density. You can read a complete overview of the project and its results in
the [report](report.pdf).

Focus of our study are:
- Kruskal's and Prim's algorithms for the minimum spanning tree problem; 
- Chu–Liu/Edmonds' algorithm for the minimum spanning arborescence problem;
- binary, d-ary and Fibonacci heaps data structures and counting sort.

You are welcome to read the conclusions in the final section of the
[report](report.pdf).

## Results
![Alt text](results/readme/1.png?raw=true "Performance of Prim's and Kruskal's algorithm on medium density graphs at varying size.")
---
![Alt text](results/readme/2.png?raw=true "Performance of Prim's and Kruskal's algorithm on sparse graphs at varying size.")
---
![Alt text](results/readme/3.png?raw=true "Performance of Prim's and Kruskal's algorithm on complete graphs at varying size.")
---
![Alt text](results/readme/4.png?raw=true "Performance of Prim's and Kruskal's algorithm on 500 nodes at varying density.")
---
![Alt text](results/readme/5.png?raw=true "Performance of Edmonds' algorithm on complete graphs at varying size.")
---
![Alt text](results/readme/6.png?raw=true "Performance of Edmonds' algorithm on 500 nodes graphs at varying density.")
---
![Alt text](results/readme/7.png?raw=true "Performance of Edmonds' algorithm on 500 nodes complete graphs.")
