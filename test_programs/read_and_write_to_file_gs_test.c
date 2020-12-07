#include <stdio.h>
#include <unistd.h>
#include <limits.h>

// Define read and write complete file paths
#define WRITE_PATH "/home/katrina/Documents/Project/csci5573-project/test_programs/write_to_test.txt"
#define READ_PATH "/home/katrina/Documents/Project/csci5573-project/test_programs/read_from_test.txt"

// Define line size
#define LINE_SIZE 256

void main()
{
    // open files
    FILE *fp_write, *fp_read;
    fp_read = fopen(READ_PATH, "r");
    if (!fp_read)
    {
        printf("ERROR: Unable to open read file %s", READ_PATH);
        return;
    }
    fp_write = fopen(WRITE_PATH, "a+");
    if (!fp_write)
    {
        printf("ERROR: Unable to open write file %s", WRITE_PATH);
        return;
    }


    // read from file 
    char buffer[LINE_SIZE];
    while(!feof(fp_read))
    {
        fgets(buffer, LINE_SIZE, fp_read);
        printf("%s", buffer);
        fprintf(fp_write, "%s", buffer);
    }

    printf("\n");
    fprintf(fp_write, "\n");

    fclose(fp_read);
    fclose(fp_write);

    return;
}
