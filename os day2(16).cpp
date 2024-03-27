#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.dat"

struct Employee {
    int id;
    char name[50];
    float salary;
};

// Function to add an employee to the file
void add_employee() {
    struct Employee emp;
    FILE *fp;

    // Open file in binary append mode
    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    // Write employee details to file
    fwrite(&emp, sizeof(struct Employee), 1, fp);

    fclose(fp);
}

// Function to display all employees from the file
void display_employees() {
    struct Employee emp;
    FILE *fp;

    // Open file in binary read mode
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\nEmployee details:\n");
    while (fread(&emp, sizeof(struct Employee), 1, fp) == 1) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }

    fclose(fp);
}

// Function to search for an employee by ID
void search_employee(int emp_id) {
    struct Employee emp;
    FILE *fp;
    int found = 0;

    // Open file in binary read mode
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    // Search for employee by ID
    while (fread(&emp, sizeof(struct Employee), 1, fp) == 1) {
        if (emp.id == emp_id) {
            printf("\nEmployee details:\n");
            printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found\n", emp_id);
    }

    fclose(fp);
}

int main() {
    int choice;
    int emp_id;

    while (1) {
        printf("\nEmployee Database Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_employee();
                break;
            case 2:
                display_employees();
                break;
            case 3:
                printf("Enter employee ID to search: ");
                scanf("%d", &emp_id);
                search_employee(emp_id);
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

