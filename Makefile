DEBUG = -g -O
RELEASE = -g -O3
CXXFLAGS = -std=c++20 -Wall -Wextra -march=native -mavx -mavx2 -msse2 -msse4.2 -fopenmp -funroll-loops -fno-omit-frame-pointer -I./
LDLIBS = -lgtest  -lbenchmark -lpthread

all: test

test: bin/test
	./bin/test --gtest_color=yes

bin/test: test/* *.hpp *.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(DEBUG) test/test.cpp -o bin/test $(LDLIBS)

benchmark: bin/benchmark
	./bin/benchmark --benchmark_color=yes

bin/benchmark: *.hpp *.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(RELEASE) main.cpp -o bin/benchmark $(LDLIBS)

.PHONY: clean dataset

clean:
	@rm -r ./bin
