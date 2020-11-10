#include <stdio.h>


int main() {
   FILE *fp;
   fp = fopen("/home/dylan/Desktop/OS_project_examples/test.txt", "w");
   fprintf(fp, "Testing!...\n");
   fclose(fp);
}
