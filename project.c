#include <stdio.h>
#include <string.h>

// structure for Student
typedef struct {
    int id;
    char name[50];
    float marks[5];
    float average;
    char grade;
} Student;

// Functions
void addStudent(Student students[], int *count);
void calculateAverageAndGrade(Student *student);
void searchStudent(const Student students[], int count);
void displayTopPerformers(const Student students[], int count);
void saveToFile(const Student students[], int count);
void loadFromFile(Student students[], int *count);

int main() {
    Student students[100];
    int count = 0;
    int choice;

    loadFromFile(students, &count);

    do {
        printf("\n--- Student Grade Management Menu ---\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Display Top 3 Performers\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addStudent(students, &count);
        } else if (choice == 2) {
            searchStudent(students, count);
        } else if (choice == 3) {
            displayTopPerformers(students, count);
        } else if (choice == 4) {
            printf("Exiting the program. Goodbye!\n");
            saveToFile(students, count);
        } else {
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 4);

    return 0;
}

// Adding student and their ID, Name, Marks for 5 subjects - Nafiz
void addStudent(Student students[], int *count) {
    printf("\n--- Add Student ---\n");
    Student newStudent;

    printf("Enter student ID: ");
    scanf("%d", &newStudent.id);
    printf("Enter student name: ");
    scanf(" %49[^\n]", newStudent.name);

    printf("Enter marks for 5 subjects: \n");
    for (int i = 0; i < 5; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &newStudent.marks[i]);
    }

    calculateAverageAndGrade(&newStudent);
    students[(*count)++] = newStudent;

    printf("Student added successfully!\n");
}

// Calculate average marks and grade for a student - Tanjim
void calculateAverageAndGrade(Student *student) {
    float total = 0;
    for (int i = 0; i < 5; i++) {
        total += student->marks[i];
    }
    student->average = total / 5;

    if (student->average >= 90) {
        student->grade = 'A';
    } else if (student->average >= 75) {
        student->grade = 'B';
    } else if (student->average >= 50) {
        student->grade = 'C';
    } else {
        student->grade = 'F';
    }
}

// Search for a student by ID or name - Salman
void searchStudent(const Student students[], int count) {
    printf("\n--- Search Student ---\n");
    int id;
    char name[50];
    int found = 0;

    printf("Enter student ID or name to search: ");
    scanf(" %49[^\n]", name);

    if (sscanf(name, "%d", &id) == 1) {
        for (int i = 0; i < count; i++) {
            if (students[i].id == id) {
                printf("Student Found: ID: %d, Name: %s, Average: %.2f, Grade: %c\n",
                       students[i].id, students[i].name, students[i].average, students[i].grade);
                found = 1;
                break;
            }
        }
    } else {
        for (int i = 0; i < count; i++) {
            if (strcmp(students[i].name, name) == 0) {
                printf("Student Found: ID: %d, Name: %s, Average: %.2f, Grade: %c\n",
                       students[i].id, students[i].name, students[i].average, students[i].grade);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

// Display the top 3 performing students - Abid
void displayTopPerformers(const Student students[], int count) {
    printf("\n--- Top 3 Performers ---\n");

    if (count == 0) {
        printf("No students available.\n");
        return;
    }

    Student top3[3] = {{0}};
    for (int i = 0; i < count; i++) {
        if (students[i].average > top3[0].average) {
            top3[2] = top3[1];
            top3[1] = top3[0];
            top3[0] = students[i];
        } else if (students[i].average > top3[1].average) {
            top3[2] = top3[1];
            top3[1] = students[i];
        } else if (students[i].average > top3[2].average) {
            top3[2] = students[i];
        }
    }

    printf("Top Performers:\n");
    for (int i = 0; i < 3; i++) {
        if (top3[i].average != 0) {
            printf("%d. ID: %d, Name: %s, Average: %.2f, Grade: %c\n",
                   i + 1, top3[i].id, top3[i].name, top3[i].average, top3[i].grade);
        }
    }
}

// Save student data to students.txt  - Salman
void saveToFile(const Student students[], int count) {
    FILE *file = fopen("students.txt", "w");
    if (!file) {
        printf("Could not open file for writing.\n");
        return;
    }

    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %.2f %.2f %.2f %.2f %.2f %c\n", 
                students[i].id, students[i].name,
                students[i].marks[0], students[i].marks[1], students[i].marks[2],
                students[i].marks[3], students[i].marks[4], students[i].grade);
    }

    fclose(file);
}

// Load student data from students.txt - Salman
void loadFromFile(Student students[], int *count) {
    FILE *file = fopen("students.txt", "r");
    if (!file) {
        return;
    }

    fscanf(file, "%d", count);
    for (int i = 0; i < *count; i++) {
        fscanf(file, "%d %49[^\n] %f %f %f %f %f %c", 
               &students[i].id, students[i].name,
               &students[i].marks[0], &students[i].marks[1], &students[i].marks[2],
               &students[i].marks[3], &students[i].marks[4], &students[i].grade);
        calculateAverageAndGrade(&students[i]); 
    }

    fclose(file);
}
