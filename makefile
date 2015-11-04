#makefile for project 1

all : encrypt

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

test :
	@echo "infile1 Buffer: 1"
	@./encrypt in/infile1 out/outfile 1 >> temp
	@diff out/outfile1 out/outfile
	@echo "infile1 Buffer: 10"
	@./encrypt in/infile1 out/outfile 10 >> temp
	@diff out/outfile1 out/outfile
	@echo "infile1 Buffer: 100"
	@./encrypt in/infile1 out/outfile 100 >> temp
	@diff out/outfile1 out/outfile
	@echo "infile2 Buffer: 1"
	@./encrypt in/infile2 out/outfile 1 >> temp
	@diff out/outfile2 out/outfile
	@echo "infile2 Buffer: 10"
	@./encrypt in/infile2 out/outfile 10 >> temp
	@diff out/outfile2 out/outfile
	@echo "infile2 Buffer: 100"
	@./encrypt in/infile2 out/outfile 100 >> temp
	@diff out/outfile2 out/outfile
	@rm temp
