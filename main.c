#include <stdlib.h> /* printf, scanf */

#include "util.h"

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Incorrect number of arguments.\n");
    return 0;
  }

  printf("Enter buffer size: ");
  scanf("%d", &buffSize);

  if (!init(argv[1], argv[2])) {
    return 0;
  }

  pthread_t t1,t2,t3,t4,t5;

  pthread_create(&t5, NULL, writeFile, NULL);
  pthread_create(&t4, NULL, incrementOut, NULL);
  pthread_create(&t3, NULL, encrypt, NULL);
  pthread_create(&t2, NULL, incrementIn, NULL);
  pthread_create(&t1, NULL, readFile, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);
  pthread_join(t5, NULL);

  destroy();

  printCounters();

	return 0;
}
