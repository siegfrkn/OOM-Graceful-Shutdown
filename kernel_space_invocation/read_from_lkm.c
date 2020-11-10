#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_NAME "/dev/call_usr_example"

static char buff[10];

int main() {
  int length = 5000;
  int file = 0;
  int bytes_read = 0;
  file = open(DEVICE_NAME, O_RDONLY);
  if (file == -1) {
    printf("Failed to open device");
  }
  bytes_read = read(file, buff, length);
  return 0;
}
