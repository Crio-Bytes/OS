#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int *t = NULL;

  // TODO: print the addresses returned
  // by malloc each time
  t = (int *)(malloc(sizeof(int)));
  t = (int *)(malloc(sizeof(int)));
  t = (int *)(malloc(sizeof(int)));
  t = (int *)(malloc(sizeof(int)));
  t = (int *)(malloc(sizeof(int)));

  return 0;
}
