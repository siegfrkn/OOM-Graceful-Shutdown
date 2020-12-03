#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define PATH "/home/dylan/Desktop/csci5573-project/kernel_space_invocation/"

int main() {
  FILE *fp;
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
  fp = fopen(PATH"test.txt", "w+");
  fprintf(fp, "This is the directory of the program running: %s\n", cwd);
  fclose(fp);
  return 0;
}
