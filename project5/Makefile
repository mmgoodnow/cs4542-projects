all: release

release: p5.cpp
	g++ --std=c++17 -o p5 p5.cpp -O3

debug: p5.cpp
	g++ --std=c++17 -o p5 p5.cpp

clean:
	rm -f p5

.PHONY: clean
