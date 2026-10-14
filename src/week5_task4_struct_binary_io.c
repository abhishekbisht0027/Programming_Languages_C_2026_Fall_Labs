// week5_task4_struct_binary_io.c   (BONUS)
// Name: Abhishek Surname: Bisht Student ID: 241ADB121
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
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

// Function prototypes (do not change these signatures - the autograder calls them directly)
int save_student_binary(const Student *s, const char *filename); // 0 on success, -1 on error
int load_student_binary(const char *filename, Student *out);     // 0 on success, -1 on error
long file_size(const char *filename);                            // bytes, -1 on error

int main(void) {
    Student s1 = {0};           // zero-initialised so unused name bytes are not garbage on disk
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";

    printf("Saving student in binary format...\n");
    if (save_student_binary(&s1, bin_file) != 0) {
        printf("Error saving binary file.\n");
        return EXIT_FAILURE;
    }

    // Save the same record as text ("name age gpa") to txt_file for comparison
    FILE *ftxt = fopen(txt_file, "w");
    if (ftxt != NULL) {
        fprintf(ftxt, "%s %d %f\n", s1.name, s1.age, s1.gpa);
        fclose(ftxt);
    } else {
        printf("Error saving text file.\n");
    }

    printf("Loading student from binary file...\n");
    if (load_student_binary(bin_file, &loaded) != 0) {
        printf("Error loading binary file.\n");
        return EXIT_FAILURE;
    }

    // Print loaded data and file sizes
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    printf("Text file size: %ld bytes\n", file_size(txt_file));
    printf("Binary file size: %ld bytes\n", file_size(bin_file));

    return EXIT_SUCCESS;
}

// Implement save_student_binary()
int save_student_binary(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return -1;
    }
    
    size_t written = fwrite(s, sizeof(Student), 1, fp);
    fclose(fp);
    
    return (written == 1) ? 0 : -1;
}

// Implement load_student_binary()
int load_student_binary(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }
    
    size_t read_count = fread(out, sizeof(Student), 1, fp);
    fclose(fp);
    
    return (read_count == 1) ? 0 : -1;
}

// Implement file_size()
long file_size(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }
    
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    
    return size;
}