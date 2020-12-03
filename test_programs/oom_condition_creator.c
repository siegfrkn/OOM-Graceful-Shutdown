#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000000000

int main() {
  printf("PID is: %d", getpid());
  fflush(stdout);
  long unsigned int i = 1;
  while(1) {
    sleep(1);
    void* huge_leak = malloc(SIZE);
    memset(huge_leak, '0', SIZE);
    printf("%lu bytes lost so far!\n", i * SIZE);
    i += 1;
  }
  return 0;
}
