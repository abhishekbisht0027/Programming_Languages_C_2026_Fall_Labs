// week5_task1_file_io.c
// Name: Abhishek Surname: Bisht Student ID: 241ADB121
//
// Task 1: Read and write data from text files
// Week 5 - Files & Modular Programming

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_FILENAME "data.txt"
#define LINE_LEN 256

int main(int argc, char* argv[]) {
  FILE* fp = NULL;
  const char* filename = DEFAULT_FILENAME;
  char line[LINE_LEN];
  int line_count = 0;

  // BONUS: if a file name was given on the command line, use argv[1]
  if (argc > 1) {
    filename = argv[1];
  }

  // 1. Print message and open the file for writing (mode "w")
  printf("Writing lines to %s...\n", filename);
  fp = fopen(filename, "w");

  // 2. Check that fp is not NULL.
  if (fp == NULL) {
    perror(filename);
    return EXIT_FAILURE;
  }

  // 3. Write lines of text to the file using fprintf()
  fprintf(fp, "Hello, file I/O in C!\n");
  fprintf(fp, "This is another line.\n");

  // 4. Close the file
  fclose(fp);

  // 5. Open the file again for reading (mode "r") and check for NULL
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror(filename);
    return EXIT_FAILURE;
  }

  // 6. Print "Reading contents:" and use fgets() in a loop
  printf("Reading contents:\n");
  while (fgets(line, LINE_LEN, fp) != NULL) {
    printf("%s", line);
    line_count++;
  }

  // 7. Close the file
  fclose(fp);

  // BONUS: print line count
  printf("Lines read: %d\n", line_count);

  return EXIT_SUCCESS;
}