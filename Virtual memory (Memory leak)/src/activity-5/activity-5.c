#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
  int *i = NULL;
  unsigned long *t = NULL;

  printf("Process ID: %d\n", getpid());

  while (1)
  {
    // TODO: resolve all the memory leaks
    i = (int *)(malloc(5e6 * sizeof(int)));
    printf("%p\t", i);
    free(i);
    t = (unsigned long *)(malloc(5e6 * sizeof(unsigned long)));
    printf("%p\n", t);
    sleep(2);
  }

  return 0;
}
