#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 1000000000
#define SHMSZ 13

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
  int shmid;
  char *shm, *s, *message;
  key_t key = 5309;

  if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0){
    perror("Error with shmget");
    exit(1);
  }

  if ((shm = shmat(shmid, NULL, 0)) == (void *)-1){
    perror("Error with shmat");
    exit(1);
  }

  message = (char *)shm;

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
    sprintf(message, "This is a string written to a region of shared memory.\n");
    i += 1;
  }
  return 0;
}