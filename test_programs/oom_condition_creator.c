#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000000000

void myflush ( FILE *in )
{
  int ch;

  do
    ch = fgetc ( in ); 
  while ( ch != EOF && ch != '\n' ); 

  clearerr ( in );
}

void mypause ( void ) 
{ 
  printf ( "\nPress [Enter] to begin oom condition creator test file . . ." );
  fflush ( stdout );
  getchar();
} 

int main()
{
  printf("PID is: %d", getpid());
  fflush(stdout);
  long unsigned int i = 1;

  mypause();
  while(1)
  {
    sleep(1);
    void* huge_leak = malloc(SIZE);
    memset(huge_leak, '0', SIZE);
    printf("%lu bytes lost so far!\n", i * SIZE);
    fflush ( stdout );
    i += 1;
  }
  return 0;
}
