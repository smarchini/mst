# Experimental Evaluation of MST Algorithms
Experimental analysis on the impact of different algorithms and heap-based data
structures for solving the minimal spanning tree problem on directed and
undirected graphs. The goal is to identify strengths and weaknesses of various
approaches. The study is conducted on random graphs of various size and density.
You can read a complete overview of the project and its results in the
[report](report.pdf).

Focus of our study are:
- Kruskal's and Prim's algorithms for the minimum spanning tree problem; 
- Chu–Liu/Edmonds' algorithm for the minimum spanning arborescence problem;
- binary, d-ary and Fibonacci heap data structures and counting sort.

I welcome you to read the conclusions in the final section of the report.

## How to use it
Install [googletest](https://github.com/google/googletest) and
[benchmark](https://github.com/google/benchmark), then:
- `make test`: compiles and runs the tests; and
- `make benchmark`: compiles and runs the benchmarks.

The plots have been drawn with Python's Matplotlib. The scripts used to generate
the plots in the report are made available in the [results](results) directory.
They are not intended to be reused; nevertheless, you can give it a shot by
generating your own `.bench` data with, for example, `./bin/size >
results/mst-size.bench`. In this case, you should probably tweak
[main.cpp](main.cpp) as you like; for example, you might want to comment out the
stuff you don't need and set custom `nodes`, `degrees` and `weights` parameters.

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
