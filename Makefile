all: main.cpp main.h processData.h processData.cpp dbLib.h dbLib.cpp
	g++ main.h main.cpp processData.h processData.cpp dbLib.h dbLib.cpp -o main
run :
	./main in.txt out.txt