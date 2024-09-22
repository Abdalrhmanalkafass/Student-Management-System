/* main.c
 *   C_project
 *  Created on: Aug 8, 2024
 *     Author: Alkafass
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// Definition of a student structure
struct student {
    int id;                // Student ID
    char name[50];         // Student name
    int age;               // Student age
    float gpa;             // Student GPA
};

// Definition of a node structure in the linked list
struct node {
    struct student data;   // Student data
    struct node *next;    // Pointer to the next node
};

struct node *head = NULL;  // Head of the linked list

// Function to add a new student to the linked list
void addStudent(const struct student *const ptr) {
    struct node *loop = NULL;

    // Check if student ID already exists
    loop = head;
    while (loop != NULL) {
        if (loop->data.id == ptr->id) {
            printf("\n[Error] Student with ID %d already exists.\n\n", ptr->id);
            return;
        }
        loop = loop->next;
    }

    // Create a new node
    struct node *link = (struct node *)malloc(sizeof(struct node));
    if (link == NULL) {
        printf("\n[Error] Cannot allocate memory for new node.\n\n");
        return;
    }

    // If the list is empty, set the new node as the head
    if (head == NULL) {
        head = link;
    } else {
        // Otherwise, add the new node at the end of the list
        loop = head;
        while (loop->next != NULL) {
            loop = loop->next;
        }
        loop->next = link;
        link->next = NULL;
    }

    // Copy student data into the new node
    link->data.id = ptr->id;
    link->data.age = ptr->age;
    link->data.gpa = ptr->gpa;
    for (int i = 0; i < 50; i++) {
        link->data.name[i] = ptr->name[i];
    }

    printf("\n[Success] Student with ID %d added successfully.\n\n", ptr->id);
}

// Function to display all students in the linked list
void displayStudents(void) {
    struct node *loop;

    if (head == NULL) {
        printf("\n[Info] No students available.\n\n");
        return;
    }

    printf("---------------------------------------------------\n");
    printf("| %-5s | %-20s | %-5s | %-5s |\n", "ID", "Name", "Age", "GPA");
    printf("---------------------------------------------------\n");

    loop = head;
    while (loop != NULL) {
        printf("| %-5d | %-20s | %-5d | %-5.2f |\n",
               loop->data.id, loop->data.name, loop->data.age, loop->data.gpa);
        loop = loop->next;
    }

    printf("---------------------------------------------------\n\n");
}

// Function to search for a student by ID
void searchStudentByID(int id) {
    struct node *loop = NULL;

    if (head == NULL) {
        printf("\n[Info] No students available.\n\n");
        return;
    }

    loop = head;
    while (loop != NULL) {
        if (loop->data.id == id) {
            printf("\n[Success] Student found:\n");
            printf("---------------------------------------------------\n");
            printf("| %-5s | %-20s | %-5s | %-5s |\n", "ID", "Name", "Age", "GPA");
            printf("---------------------------------------------------\n");
            printf("| %-5d | %-20s | %-5d | %-5.2f |\n",
                   loop->data.id, loop->data.name, loop->data.age, loop->data.gpa);
            printf("---------------------------------------------------\n\n");
            return;
        }
        loop = loop->next;
    }

    printf("\n[Error] Student with ID %d not found.\n\n", id);
}

// Function to search for the student with the highest GPA
void searchHighestGPA(void) {
    struct node *loop = NULL;
    struct node *maxptr = NULL;
    float maxGPA = -1.0; // Initialize to a value lower than any possible GPA

    if (head == NULL) {
        printf("\n[Info] No students available.\n\n");
        return;
    }

    loop = head;
    while (loop != NULL) {
        if (loop->data.gpa > maxGPA) {
            maxGPA = loop->data.gpa;
            maxptr = loop;
        }
        loop = loop->next;
    }

    if (maxptr != NULL) {
        printf("\n[Success] Student with highest GPA:\n");
        printf("---------------------------------------------------\n");
        printf("| %-5s | %-20s | %-5s | %-5s |\n", "ID", "Name", "Age", "GPA");
        printf("---------------------------------------------------\n");
        printf("| %-5d | %-20s | %-5d | %-5.2f |\n",
               maxptr->data.id, maxptr->data.name, maxptr->data.age, maxptr->data.gpa);
        printf("---------------------------------------------------\n\n");
    }
}

// Function to delete a student by ID
void deleteStudent(int id) {
    struct node *current = NULL;
    struct node *prev = NULL;

    if (head == NULL) {
        printf("\n[Info] No students available.\n\n");
        return;
    }

    current = head;
    while (current != NULL && current->data.id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("\n[Error] Student with ID %d not found.\n\n", id);
        return;
    }

    if (current == head) {
        head = head->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("\n[Success] Student with ID %d successfully deleted.\n\n", id);
}

// Function to calculate the average GPA of all students
float calculateAverageGPA(void) {
    struct node *loop = NULL;
    int count = 0;
    float sum = 0;

    if (head == NULL) {
        printf("\n[Info] No students available.\n\n");
        return 0.0;
    }

    loop = head;
    while (loop != NULL) {
        sum += loop->data.gpa;
        count++;
        loop = loop->next;
    }

    float avg = (count > 0) ? (sum / count) : 0.0;
    printf("\n[Info] Calculating average GPA:\n");
    printf("---------------------------------------------------\n");
    printf("| %-5s | %-5s |\n", "Count", "Average GPA");
    printf("---------------------------------------------------\n");
    printf("| %-5d | %-5.2f |\n", count, avg);
    printf("---------------------------------------------------\n\n");

    return avg;
}

// Function to update student details by ID
void updateStudent(int id) {
    struct node *current = NULL;

    if (head == NULL) {
        printf("\n[Info] No students available.\n\n");
        return;
    }

    current = head;
    while (current != NULL && current->data.id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("\n[Error] Student with ID %d not found.\n\n", id);
        return;
    }

    printf("\n[Info] Updating student details for ID %d:\n", id);
    printf("Please enter the new student name:\n");
    scanf("%s", current->data.name);
    printf("Please enter the new student ID:\n");
    scanf("%d", &(current->data.id));
    printf("Please enter the new student age:\n");
    scanf("%d", &(current->data.age));
    printf("Please enter the new student GPA:\n");
    scanf("%f", &(current->data.gpa));

    printf("\n[Success] Student details updated successfully.\n\n");
}

// Main function to interact with the user
int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    while (1) {
        printf("===================================\n");
        printf("            Student Menu           \n");
        printf("===================================\n");
        printf("1: Add student\n");
        printf("2: Display students\n");
        printf("3: Search by ID\n");
        printf("4: Update student by ID\n");
        printf("5: Delete student by ID\n");
        printf("6: Calculate average GPA\n");
        printf("7: Search for highest GPA\n");
        printf("8: Exit\n");
        printf("Choose operation: ");

        int press;
        int id;
        scanf("%d", &press);

        switch (press) {
            case 1: {
                struct student s1;
                printf("\nPlease enter the student name: ");
                scanf("%s", s1.name);
                printf("Please enter the student ID: ");
                scanf("%d", &s1.id);
                printf("Please enter the student age: ");
                scanf("%d", &s1.age);
                printf("Please enter the student GPA: ");
                scanf("%f", &s1.gpa);
                addStudent(&s1);
                break;
            }
            case 2:
                displayStudents();
                break;
            case 3:
                printf("\nPlease enter the student ID: ");
                scanf("%d", &id);
                searchStudentByID(id);
                break;
            case 4:
                printf("\nPlease enter the student ID: ");
                scanf("%d", &id);
                updateStudent(id);
                break;
            case 5:
                printf("\nPlease enter the student ID: ");
                scanf("%d", &id);
                deleteStudent(id);
                break;
            case 6:
                calculateAverageGPA();
                break;
            case 7:
                searchHighestGPA();
                break;
            case 8:
                printf("\nExiting the program. Goodbye!\n");
                return 0;
            default:
                printf("\n[Error] Invalid operation. Please try again.\n\n");
        }
    }
}
