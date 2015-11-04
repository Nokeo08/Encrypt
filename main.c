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

  if (!initFiles(argv[1], argv[2])) {
    return 0;
  }

  while (readFile()) {
    incrementIn();
    encrypt();
    incrementOut();
    writeFile();
  }
  incrementIn();
  encrypt();
  incrementOut();
  writeFile();

  closeFiles();

  printCounters();

	return 0;
}
