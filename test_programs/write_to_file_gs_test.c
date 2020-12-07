#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define PATH "/home/katrina/Documents/Project/csci5573-project/test_programs/graceful_shutdown_output.txt"

int main()
{
    FILE *fp;
    char cwd[PATH_MAX];

    // check current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
       printf("Current working dir: %s\n", cwd);
    } else {
       perror("getcwd() error");
       return 1;
    }

    // write to file
    fp = fopen(PATH, "w+");
    fprintf(fp, "The oom killer was invoked, and this is a file generated as a result of the graceful shutdown\n");
    fclose(fp);

    return 0;
}
