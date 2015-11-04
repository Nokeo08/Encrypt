#include <stdio.h>
#include <pthread.h>

#ifndef _UTIL_PROJ2_H_
#define _UTIL_PROJ2_H_


FILE* infile;
FILE* outfile;
int buffSize;
int selection;
char* buffer;
int* incounter;
int* outcounter;

int initFiles(char* infileName, char* outfileName);
void closeFiles();

int readFile();
int writeFile();


int* initCounter();
int incrementIn();
int incrementOut();
int increment(char c, int* counter);
void printCounters();


char getLeter(int i);
int encrypt();
char encryptChar(char c, int* s);

#endif
