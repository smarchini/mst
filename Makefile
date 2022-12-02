CXXFLAGS += -std=c++20 -march=native -mtune=native -Wall -Wextra -I ./mst
LDLIBS += -lgtest -lbenchmark -lpthread
DEPENDENCIES = $(shell find . -name "*.[ch]pp")
DEBUG := -g -O0 -funroll-loops -fno-omit-frame-pointer
RELEASE := -O3

all: test benchmark

test: bin/test
	./bin/test --gtest_color=yes

bin/test: test/test.cpp $(DEPENDENCIES)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $@ $< $(LDLIBS)

benchmark: bin/density bin/size
	./bin/density --benchmark_color=yes
	./bin/size --benchmark_color=yes

bin/density: main.cpp $(DEPENDENCIES)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(RELEASE) -DDENSITYBENCH -o $@ $< $(LDLIBS)

bin/size: main.cpp $(DEPENDENCIES)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(RELEASE) -DSIZEBENCH -o $@ $< $(LDLIBS)

.PHONY: clean dataset

clean:
	@rm -r ./bin
