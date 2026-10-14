// week5_task3_student_management_system.c
// Name: Abhishek Surname: Bisht Student ID: 241ADB121
//
// Task 3: Mini-project - Student management system with file persistence
// Week 5 - Files & Modular Programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
  char name[NAME_LEN];
  int id;
  float gpa;
} Student;

// Function prototypes (do not change these signatures)
int load_students(Student arr[], int max);
int save_students(const Student arr[], int count);
void add_student(Student arr[], int* count);
void list_students(const Student arr[], int count);
int read_line(const char* prompt, char* buf, size_t size);

int main(void) {
  Student students[MAX_STUDENTS];
  int count = 0;
  char input[LINE_LEN];
  int running = 1;

  // Load existing data
  count = load_students(students, MAX_STUDENTS);
  printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

  while (running) {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");

    int choice;
    if (read_line("Select an option: ", input, sizeof(input)) != 0) {
      choice = 3;  // end of input: save and exit
    } else {
      char* end;
      long value = strtol(input, &end, 10);
      choice = (end != input && *end == '\0') ? (int)value : 0;
    }

    switch (choice) {
      case 1:
        list_students(students, count);
        break;
      case 2:
        add_student(students, &count);
        break;
      case 3:
        if (save_students(students, count) == -1) {
          printf("Error saving data.\n");
        } else {
          printf("Data saved. Goodbye!\n");
        }
        running = 0;
        break;
      default:
        printf("Invalid option. Try again.\n");
    }
  }

  return EXIT_SUCCESS;
}

// Provided helper - prints a prompt and reads one line from stdin into buf.
int read_line(const char* prompt, char* buf, size_t size) {
  printf("%s", prompt);
  fflush(stdout);
  if (fgets(buf, (int)size, stdin) == NULL) {
    return -1;
  }
  size_t len = strcspn(buf, "\r\n");
  if (buf[len] == '\0' && len == size - 1) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
  }
  buf[len] = '\0';
  return 0;
}

// Implement load_students()
int load_students(Student arr[], int max) {
  FILE* fp = fopen(DATA_FILE, "r");
  if (fp == NULL) {
    return 0;  // First run, file does not exist
  }

  char line[LINE_LEN];
  int loaded = 0;

  while (loaded < max && fgets(line, sizeof(line), fp) != NULL) {
    char temp_name[NAME_LEN];
    int temp_id;
    float temp_gpa;

    // Parse "name,id,gpa"
    if (sscanf(line, "%49[^,],%d,%f", temp_name, &temp_id, &temp_gpa) == 3) {
      strcpy(arr[loaded].name, temp_name);
      arr[loaded].id = temp_id;
      arr[loaded].gpa = temp_gpa;
      loaded++;
    }
  }

  fclose(fp);
  return loaded;
}

// Implement save_students()
int save_students(const Student arr[], int count) {
  FILE* fp = fopen(DATA_FILE, "w");
  if (fp == NULL) {
    return -1;
  }

  for (int i = 0; i < count; i++) {
    fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
  }

  fclose(fp);
  return 0;
}

// Implement add_student()
void add_student(Student arr[], int* count) {
  if (*count >= MAX_STUDENTS) {
    printf("Cannot add more students (limit reached).\n");
    return;
  }

  char name_buf[LINE_LEN];
  char id_buf[LINE_LEN];
  char gpa_buf[LINE_LEN];

  if (read_line("Enter name: ", name_buf, sizeof(name_buf)) != 0) return;
  if (read_line("Enter ID: ", id_buf, sizeof(id_buf)) != 0) return;
  if (read_line("Enter GPA: ", gpa_buf, sizeof(gpa_buf)) != 0) return;

  // Validate Name: not empty and no commas
  if (strlen(name_buf) == 0 || strchr(name_buf, ',') != NULL) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  // Validate ID: must be a valid integer
  char* endptr;
  int id = (int)strtol(id_buf, &endptr, 10);
  if (*endptr != '\0' || strlen(id_buf) == 0) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  // Validate GPA: must be a number between 0.0 and 4.0
  float gpa = strtof(gpa_buf, &endptr);
  if (*endptr != '\0' || strlen(gpa_buf) == 0 || gpa < 0.0f || gpa > 4.0f) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  // Add to array
  strcpy(arr[*count].name, name_buf);
  arr[*count].id = id;
  arr[*count].gpa = gpa;
  (*count)++;

  printf("Student added successfully!\n");
}

// Implement list_students()
void list_students(const Student arr[], int count) {
  if (count == 0) {
    printf("No students found.\n");
    return;
  }

  printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
  for (int i = 0; i < count; i++) {
    printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
  }
}