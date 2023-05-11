all: main.cpp matrix.o number.o
	g++ main.cpp matrix.o number.o -o matrix

asm: main.cpp
	g++ -S main.cpp

matrix.o: matrix.cpp
	g++ -c matrix.cpp

number.o: number.cpp
	g++ -c number.cpp
