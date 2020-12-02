#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("PID is: %d", getpid());
  fflush(stdout);
  while(1) {
    sleep(0.01);
    void* huge_leak = malloc(100000000);
  }
  return 0;
}
