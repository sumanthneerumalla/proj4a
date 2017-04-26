CXXFLAGS = -Wall -g

Driver.out: MinMaxHeap.cpp MinMaxHeap.h test1.cpp
		g++ $(CXXFLAGS) MinMaxHeap.cpp MinMaxHeap.h test1.cpp -o Driver.out

Driver1.out: MinMaxHeap.cpp MinMaxHeap.h main.cpp
		g++ $(CXXFLAGS) MinMaxHeap.cpp MinMaxHeap.h main.cpp -o Driver1.out

make all:
	make Driver.out


make clean:
		rm -rf *.o
		rm -rf *~
		rm -rf *.out

make test:
		make Driver1.out;
		./Driver1.out

make run:
		make;
		./Driver.out