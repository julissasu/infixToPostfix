#Makefile

all: in2post.x

in2post.x: in2post.cpp stack.hpp
	g++ in2post.cpp -o in2post.x -std=c++11

clean:
	rm -f *.o *.x
