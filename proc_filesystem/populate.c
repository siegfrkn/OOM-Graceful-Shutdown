
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// currently not appending
 
void main( int argc, char *argv[] )
{
	char *str1, *str2;
	char buf[100];
	printf("second arg: %s\n", argv[2]);
	str2 = argv[2];

   if( argc >= 2 ) {
      printf("The argument supplied is %s %s\n", argv[1], argv[2]);
      str1 = argv[1];
      strcat(str1, " ");
      printf("intermed string: %s\n", str1);
      printf("second arg: %s\n", argv[2]);
      strcat(str1, str2);
      printf("The new string is %s\n", str1);
   }

	int fd = open("/proc/graceful_shutdown", O_RDWR);
	read(fd, buf, 100);
	puts(buf);
 
	lseek(fd, 0 , SEEK_END);
	write(fd, str2, 100);
	
	lseek(fd, 0 , SEEK_END);
	read(fd, buf, 100);
	// puts(buf);
}	