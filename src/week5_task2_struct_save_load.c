// week5_task2_struct_save_load.c
// Name: Abhishek Surname: Bisht Student ID: 241ADB121
//
// Task 2: Save and load structured records from a file
// Week 5 - Files & Modular Programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
  char name[MAX_NAME_LEN];
  int age;
  float gpa;
} Student;

// Function prototypes (do not change these signatures)
int save_student(const Student* s,
                 const char* filename);  // 0 on success, -1 on error
int load_student(const char* filename,
                 Student* out);  // 0 on success, -1 on error

int main(void) {
  Student s1 = {0};
  strcpy(s1.name, "Alice");
  s1.age = 21;
  s1.gpa = 3.75f;

  Student loaded = {0};
  const char* filename = "student.txt";

  printf("Saving student to file...\n");
  if (save_student(&s1, filename) != 0) {
    printf("Error saving student to file.\n");
    return EXIT_FAILURE;
  }

  printf("Loading student from file...\n");
  if (load_student(filename, &loaded) != 0) {
    printf("Error loading student from file.\n");
    return EXIT_FAILURE;
  }

  // Print the loaded data in exactly this format
  printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age,
         loaded.gpa);

  return EXIT_SUCCESS;
}

// Implement save_student()
int save_student(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    return -1;
  }

  // write "name age gpa" on one line
  fprintf(fp, "%s %d %f\n", s->name, s->age, s->gpa);
  fclose(fp);

  return 0;
}

// Implement load_student()
int load_student(const char* filename, Student* out) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    return -1;
  }

  // read the three fields and check that it returned 3
  if (fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa) != 3) {
    fclose(fp);
    return -1;
  }

  fclose(fp);
  return 0;
}