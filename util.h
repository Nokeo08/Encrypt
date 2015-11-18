#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#ifndef _UTIL_PROJ2_H_
#define _UTIL_PROJ2_H_

/* Counters */
int readerIndex, inCounterIndex, encriptionIndex, outCounterIndex, writerIndex;

/* Semephores */
sem_t inEmptyCounter, inEmptyEncrypter, inFullCounter, inFullEncrypter;
sem_t outEmptyCounter, outEmptyWriter, outFullCounter, outFullWriter;

pthread_mutex_t mut;

FILE* infile;
FILE* outfile;

int buffSize;
int selection;

/* input and output buffers */
char* inbuffer;
char* outbuffer;

/* Counters for the input and output buffers */
int* incounter;
int* outcounter;

/* Setup and Cleanup */
int init(char* infileName, char* outfileName);
void destroy();

/* Threads */
void* readFile();
void* incrementIn();
void* encrypt();
void* incrementOut();
void* writeFile();

/* Counter functions */
int increment(char c, int* counter);
void printCounters();

/* MISC */
char getLeter(int i);

/* Encryption */
char encryptChar(char c, int* s);

#endif
