#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
  int *t = NULL;

  printf("Process ID: %d\n", getpid());

  while (1)
  {
    // TODO: allocate 100 MB memory every
    // 2 seconds
    t = (int *)(malloc(sizeof(int)));
    printf("%p\n", t);
    sleep(1);
  }

  return 0;
}
