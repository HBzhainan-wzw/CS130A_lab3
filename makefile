all: project3.out

project1b.out: project3.cpp Graph.cpp GraphGen.cpp 
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out