#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float marks[4]; 
    float average;  
    char grade;   
} Student;

// Function to add a new student and calculate their average marks and grade - Salman
void addStudentAndCalculate(Student students[], int *count) {
    printf("\n--- Add Student ---\n");
    Student newStudent;

    printf("Enter student ID: ");
    scanf("%d", &newStudent.id);
    printf("Enter student name: ");
    scanf(" %49[^\n]", newStudent.name);

    printf("Enter marks for the following subjects (0-100):\n");
    printf("Physics: ");
    scanf("%f", &newStudent.marks[0]);
    printf("Math: ");
    scanf("%f", &newStudent.marks[1]);
    printf("EEE: ");
    scanf("%f", &newStudent.marks[2]);
    printf("CSE: ");
    scanf("%f", &newStudent.marks[3]);

    for (int i = 0; i < 4; i++) {
        if (newStudent.marks[i] < 0 || newStudent.marks[i] > 100) {
            printf("Invalid marks entered. Please enter marks between 0 and 100.\n");
            return;
        }
    }

    float total = 0;
    for (int i = 0; i < 4; i++) {
        total += newStudent.marks[i];
    }
    newStudent.average = total / 4; 

    if (newStudent.average >= 90) {
        newStudent.grade = 'A';
    } else if (newStudent.average >= 75) {
        newStudent.grade = 'B';
    } else if (newStudent.average >= 50) {
        newStudent.grade = 'C';
    } else {
        newStudent.grade = 'F';
    }

    students[(*count)++] = newStudent;

    printf("Student added successfully!\n");
}

// Function to search for a student by ID or name - Nafiz
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

// Function to display the top 3 performing students - Tanjim
void displayTopPerformers(const Student students[], int count) {
    printf("\n--- Top 3 Performers ---\n");

    if (count == 0) {
        printf("No students available.\n");
        return;
    }

    Student top3[3] = {{0, "", {0, 0, 0, 0}, 0.0, 'F'}, {0, "", {0, 0, 0, 0}, 0.0, 'F'}, {0, "", {0, 0, 0, 0}, 0.0, 'F'}};

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

// Function to save or load student data to/from students.txt - Abid
void manageFile(Student students[], int *count, int save) {
    FILE *file;
    if (save) {
        file = fopen("students.txt", "w");
        if (!file) {
            printf("Could not open file for writing.\n");
            return;
        }

        fprintf(file, "%d\n", *count);
        for (int i = 0; i < *count; i++) {
            fprintf(file, "%d %s %.2f %.2f %.2f %.2f %c\n", 
                    students[i].id, students[i].name,
                    students[i].marks[0], students[i].marks[1], students[i].marks[2],
                    students[i].marks[3], students[i].grade);
        }

        fclose(file);
    } else {
        file = fopen("students.txt", "r");
        if (!file) {
            printf("Could not open file for reading.\n");
            return;
        }

        fscanf(file, "%d", count);
        for (int i = 0; i < *count; i++) {
            fscanf(file, "%d %49[^\n] %f %f %f %f %c", 
                   &students[i].id, students[i].name,
                   &students[i].marks[0], &students[i].marks[1], &students[i].marks[2],
                   &students[i].marks[3], &students[i].grade);
        }

        fclose(file);
    }
}

int main() {
    Student students[100]; 
    int count = 0;         
    int choice;

    manageFile(students, &count, 0); 

    do {
        printf("\n--- Student Grade Management Menu ---\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Display Top 3 Performers\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addStudentAndCalculate(students, &count); 
        } else if (choice == 2) {
            searchStudent(students, count); 
        } else if (choice == 3) {
            displayTopPerformers(students, count); 
        } else if (choice == 4) {
            printf("Exiting the program. Goodbye!\n");
            manageFile(students, &count, 1);
        } else {
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
