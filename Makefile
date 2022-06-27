DEBUG = -g -O
RELEASE = -g -O3
CXXFLAGS = -std=c++20 -Wall -Wextra -march=native -mavx -mavx2 -msse2 -msse4.2 -fopenmp -funroll-loops -fno-omit-frame-pointer -I./
LDLIBS = -lgtest -lbenchmark -lpthread

all: test

test: bin/test
	./bin/test --gtest_color=yes

bin/test: test/* mst/*.hpp *.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(DEBUG) -Imst test/test.cpp -o bin/test $(LDLIBS)

benchmark: bin/density bin/size
	./bin/density --benchmark_color=yes
	./bin/size --benchmark_color=yes

bin/density: *.hpp *.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(RELEASE) -Imst -DDENSITYBENCH main.cpp -o bin/density $(LDLIBS)

bin/size: *.hpp *.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(RELEASE) -Imst -DSIZEBENCH main.cpp -o bin/size $(LDLIBS)

.PHONY: clean dataset

clean:
	@rm -r ./bin
