#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int *t = NULL;

  while (1)
  {
    // TODO: print the address returned
    // by malloc every 2 seconds
    t = (int *)(malloc(sizeof(int)));
  }

  return 0;
}
