#include <stdio.h> /* FILE, fopen, fgetc */
#include <stdlib.h> /* malloc */
#include <ctype.h> /* toupper, isalpha */

#include "util.h"

int init(char* infileName, char* outfileName){

  infile = fopen(infileName, "r");
  if (infile == NULL){
    printf("Problem opening \"%s\"", infileName);
    return 0;
  }


  outfile = fopen(outfileName, "w");
  if (outfile == NULL){
    fclose(infile);
    printf("Problem opening \"%s\"", outfileName);
    return 0;
  }

  inbuffer = calloc(buffSize, sizeof(char));
  outbuffer = calloc(buffSize, sizeof(char));
  incounter = initCounter();
  outcounter = initCounter();


  selection = 1;
  first = 1;


  inProdPtr=0;
  inConPtr=0;
  inConPtrE=0;
  outConPtr=0;
  outConPtrW=0;


  sem_init(&inEmptyCounter, 0, buffSize);
  sem_init(&inEmptyEncrypter, 0, buffSize);

  sem_init(&inFullCounter, 0, 0);
  sem_init(&inFullEncrypter, 0, 0);


  sem_init(&outEmptyCounter, 0, buffSize);
  sem_init(&outEmptyWriter, 0, buffSize);

  sem_init(&outFullCounter, 0, 0);
  sem_init(&outFullWriter, 0, 0);

  pthread_mutex_init(&mut, NULL);

  return 1;
}

void destroy(){

  sem_destroy(&inEmptyCounter);
  sem_destroy(&inEmptyEncrypter);

  sem_destroy(&inFullCounter);
  sem_destroy(&inFullEncrypter);

  sem_destroy(&outEmptyCounter);
  sem_destroy(&outEmptyWriter);

  sem_destroy(&outFullCounter);
  sem_destroy(&outFullWriter);

  pthread_mutex_destroy(&mut);

  fclose(infile);
  fclose(outfile);
  free(inbuffer);
  free(outbuffer);
}

void* readFile(){
  int c = 0;

    while (EOF != c) {

      sem_wait(&inEmptyCounter);
      sem_wait(&inEmptyEncrypter);

      pthread_mutex_lock(&mut);

      c = fgetc(infile);
      inbuffer[inProdPtr] = c;
      inProdPtr = (inProdPtr+1) % buffSize;

      pthread_mutex_unlock(&mut);

      sem_post(&inFullCounter);
      sem_post(&inFullEncrypter);
    }

    return NULL;
}

void* incrementIn(){

    int go = 1;
    while (go) {
      sem_wait(&inFullCounter);

      pthread_mutex_lock(&mut);

      if (EOF != inbuffer[inConPtr]) {
        increment(inbuffer[inConPtr], incounter);
        inConPtr = (inConPtr+1) % buffSize;
      }else{
        go = 0;
      }

      pthread_mutex_unlock(&mut);

      sem_post(&inEmptyCounter);
    }
  return NULL;
}

void* encrypt(){

  int go = 1;

  while (go) {
    sem_wait(&inFullEncrypter);

    sem_wait(&outEmptyCounter);
    sem_wait(&outEmptyWriter);

    pthread_mutex_lock(&mut);

    if (EOF != inbuffer[inConPtrE]) {
      outbuffer[inConPtrE] = encryptChar(inbuffer[inConPtrE], &selection);
      inConPtrE = (inConPtrE+1) % buffSize;
    }
    else{
      outbuffer[inConPtrE] = inbuffer[inConPtrE];
      go = 0;
    }

    pthread_mutex_unlock(&mut);

    sem_post(&inEmptyEncrypter);

    sem_post(&outFullCounter);
    sem_post(&outFullWriter);
  }

  return NULL;
}

void* incrementOut(){
  int go = 1;

  while (go) {
    sem_wait(&outFullCounter);

    pthread_mutex_lock(&mut);

    if (EOF != outbuffer[outConPtr]) {
      increment(outbuffer[outConPtr], outcounter);
      outConPtr = (outConPtr+1) % buffSize;
    }else{
      go = 0;
    }

    pthread_mutex_unlock(&mut);

    sem_post(&outEmptyCounter);
  }
  return NULL;
}

void* writeFile(){
    int go = 1;

    while (go) {

      sem_wait(&outFullWriter);

      pthread_mutex_lock(&mut);

      if(EOF != outbuffer[outConPtrW])
      {
        fputc(outbuffer[outConPtrW], outfile);
        outConPtrW = (outConPtrW+1) % buffSize;
      }else{
        go = 0;
      }

      pthread_mutex_unlock(&mut);

      sem_post(&outEmptyWriter);
    }

    return NULL;
}

int* initCounter(){
    int* counter = (int*)malloc( 26*sizeof(int) );

    for(int i = 0; i < 26; i++) counter[i] = 0;

    return counter;
}

int increment(char c, int* counter){

  switch( toupper(c) )
  {
    case 'A' : counter[0]++; break;
    case 'B' : counter[1]++; break;
    case 'C' : counter[2]++; break;
    case 'D' : counter[3]++; break;
    case 'E' : counter[4]++; break;
    case 'F' : counter[5]++; break;
    case 'G' : counter[6]++; break;
    case 'H' : counter[7]++; break;
    case 'I' : counter[8]++; break;
    case 'J' : counter[9]++; break;
    case 'K' : counter[10]++; break;
    case 'L' : counter[11]++; break;
    case 'M' : counter[12]++; break;
    case 'N' : counter[13]++; break;
    case 'O' : counter[14]++; break;
    case 'P' : counter[15]++; break;
    case 'Q' : counter[16]++; break;
    case 'R' : counter[17]++; break;
    case 'S' : counter[18]++; break;
    case 'T' : counter[19]++; break;
    case 'U' : counter[20]++; break;
    case 'V' : counter[21]++; break;
    case 'W' : counter[22]++; break;
    case 'X' : counter[23]++; break;
    case 'Y' : counter[24]++; break;
    case 'Z' : counter[25]++; break;

    default : return -1;
  }

  return 1;
}

void printCounters(){
    printf("Input file contains\n");
    for(int i = 0; i < 26; i++)
      if (incounter[i] != 0) printf("%c: %d\n", getLeter(i), incounter[i]);


    printf("Output file contains\n");
    for(int i = 0; i < 26; i++)
      if (outcounter[i] != 0) printf("%c: %d\n", getLeter(i), outcounter[i]);


  free(incounter);
  free(outcounter);
}

char getLeter(int i){

  switch( i )
  {
    case 0 : return 'A';
    case 1 : return 'B';
    case 2 : return 'C';
    case 3 : return 'D';
    case 4 : return 'E';
    case 5 : return 'F';
    case 6 : return 'G';
    case 7 : return 'H';
    case 8 : return 'I';
    case 9 : return 'J';
    case 10 : return 'K';
    case 11 : return 'L';
    case 12 : return 'M';
    case 13 : return 'N';
    case 14 : return 'O';
    case 15 : return 'P';
    case 16 : return 'Q';
    case 17 : return 'R';
    case 18 : return 'S';
    case 19 : return 'T';
    case 20 : return 'U';
    case 21 : return 'V';
    case 22 : return 'W';
    case 23 : return 'X';
    case 24 : return 'Y';
    case 25 : return 'Z';
  }

  return '\0';
}

char encryptChar(char c, int* s){
  if (!isalpha(c)) {
    return c;
  }

  if (*s == 1) {
    if (c == 'z') {
      c = 'a';
    }
    else if (c == 'Z') {
      c = 'A';
    }
    else {
      c++;
    }
    *s = -1;
  }
  else if (*s == -1) {
    if (c == 'a') {
      c = 'z';
    }
    else if (c == 'A') {
      c = 'Z';
    }
    else {
      c--;
    }
    *s = 0;
  }
  else if (*s == 0) {
    *s = 1;
  }

  return c;
}
