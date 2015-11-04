#makefile for project 1

all : encrypt

run : all
	@./encrypt

clean :
	@rm -f *.o encrypt

util.o : util.c util.h
	gcc -pedantic -Wall -c util.c

main.o : main.c
	gcc -pedantic -Wall -c main.c

encrypt : main.o util.o
	gcc -pedantic -Wall -o encrypt main.o util.o
	@rm *.o
	@echo -e "\nDone Compiling encrypt\n\n"