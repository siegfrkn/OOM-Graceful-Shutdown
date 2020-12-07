#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define SHMSZ 13

int main(void){
        int i, shmid;
        char *shm, *s, *message;
	FILE *f;
	f = fopen("data.txt", "w");

	if (f == NULL){
		printf("Unable to open file.\n");
		exit(1);
	}

        key_t key = 5309;

        if ((shmid = shmget(key, SHMSZ, 0666)) < 0){
        perror("Error with shmget");
        exit(1);
        }

        if ((shm = shmat(shmid, NULL, 0)) == (void *)-1){
        perror("Error with shmat");
        exit(1);
        }

        message = (char *)shm;
	fputs(message, f);
	
	shmdt(message);
	shmctl(shmid, IPC_RMID, NULL);
        printf("Done!\n");
        

        return 0;
}

