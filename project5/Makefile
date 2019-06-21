all: release

release: p5a.cpp p5b.cpp
	g++ --std=c++17 -o p5a p5a.cpp -O3
	g++ --std=c++17 -o p5b p5b.cpp -O3

debug: p5a.cpp p5b.cpp
	g++ --std=c++17 -o p5a p5a.cpp
	g++ --std=c++17 -o p5b p5b.cpp

clean:
	rm -f p5a p5b

.PHONY: clean
