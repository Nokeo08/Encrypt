#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#ifndef _UTIL_PROJ2_H_
#define _UTIL_PROJ2_H_

int inProdPtr, inConPtr, inConPtrE, outConPtr, outConPtrW, first;

sem_t inEmptyCounter, inEmptyEncrypter, inFullCounter, inFullEncrypter;
sem_t outEmptyCounter, outEmptyWriter, outFullCounter, outFullWriter;

pthread_mutex_t mut;

FILE* infile;
FILE* outfile;
int buffSize;
int selection;
char* inbuffer;
char* outbuffer;
int* incounter;
int* outcounter;


int init(char* infileName, char* outfileName);
void destroy();

void* readFile();
void* writeFile();


int* initCounter();
void* incrementIn();
void* incrementOut();
int increment(char c, int* counter);
void printCounters();


char getLeter(int i);
void* encrypt();
char encryptChar(char c, int* s);

#endif
