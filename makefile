all: main.o readline.o findsubstr.o
	gcc -o mygrep main.o readline.o findsubstr.o
main.0 :  main.c
	gcc -c main.c
findsubstr.o :  findsubstr.h findsubstr.c
	gcc -c findsubstr.h findsubstr.c
readline.o :  readline.h readline.c
	gcc -c readline.h readline.c
clean : 
	rm -f *.o *gch

