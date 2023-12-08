//
// Created by andre on 20/11/2023.
//
// Group Number 10
//
// Members: ALONSO GARDE ALITE, LUCIAN ANDREI NEGOITA, HÉCTOR RUÍZ LÓPEZ
//
#include "library.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

// Structs

typedef struct {
    char name[20];
    char lastName[20];
    char DNI[10]; // last char is '\0'
    int monthlyHours;
    int yearlyHours;
    float hourlyRate;
    float monthlySalary;
    int workedTime;
} Employee;

// Headers

void registerEmployee(Employee company[], int size, int *currentEmployees);

void recordEntryEmployee(Employee company[], int size, int *currentEmployees, int *hourEntry, int *minEntry);

void recordExitEmployee(Employee company[], int size, int *currentEmployees, int *hourExit, int*minExit, int *hourEntry, int *minEntry, int (*hoursMonthEmployees)[31]);

int FindEmployeeIndex(Employee company[], int size,char* DNI, int *currentEmployees);

void calculateMonthlySalary(Employee company[], int size, int *(currentEmployees));

void removeEmployee(Employee company[], int size, int *currentEmployees);

void printMatriz(int (*hoursMonthEmployees)[31]);

//void printArray(Employee company, int size, int *(currentEmployees));

int main() {

    int hour = -1;
    int min = -1;
    int option = -1;
    Get_time(&hour, &min);
    int entryHour;
    int entryMin;
    int exitHour;
    int exitMin;

    int hoursMonthEmployees[20][31] = {0};

    Employee company[20] = {0};
    int currentEmployees = 0;


    do {
        printf("\n\nGavicu_Paga TIME CONTROL SYSTEM");
        printf("\n1. Register a new employee.");
        printf("\n2. Record entry time.");
        printf("\n3. Record exit time.");
        printf("\n4. Calculate monthly salary.");
        printf("\n5. Remove an employee.");
        printf("\n6. Exit the program.");

        printf("\nPlease select an option: ");

        scanf(" %d", &option);

        switch (option) {
            case 1:
                printf("\n");
                registerEmployee(company, 20, &currentEmployees);
                printf("\n");
                break;
            case 2:
                printf("\n");
                recordEntryEmployee(company, 20, &currentEmployees, &entryHour, &entryMin);
                printf("\n");
                break;
            case 3:
                printf("\n");
                recordExitEmployee(company,20,&currentEmployees, &exitHour, &exitMin, &entryHour, &entryMin, hoursMonthEmployees);
                printf("\n");
                printMatriz(hoursMonthEmployees);
                break;
            case 4:
                printf("\n");
                calculateMonthlySalary(company,20,&currentEmployees);
                printf("\n");
                break;
            case 5:
                printf("\n");
                removeEmployee(company, 20, &currentEmployees);
                printf("\n");
                break;
            case 6:
                printf("\nBye!");
                break;
            default:
                printf("\n\nTry again, option not valid!");
        }
    } while (option != 6);


    return 0;
}




// Option 1, Register New Employee

void registerEmployee(Employee company[], int size, int *currentEmployees) {

    if (*currentEmployees == 20) {
        printf("No more employees are allowed in the company.\n");
        return;
    }

    printf("\nEnter name: ");
    scanf("%19s", company[(*currentEmployees)].name);

    printf("\nEnter last name: ");
    scanf("%19s", company[(*currentEmployees)].lastName);

    printf("\nEnter DNI: ");
    scanf("%10s", company[(*currentEmployees)].DNI);

    // Rest of data is initialized at 0 by default.

    (*currentEmployees)++;
}

// Option 2, Record Entry Time

void recordEntryEmployee(Employee company[], int size, int *currentEmployees, int *hourEntry, int*minEntry) {
    char DNI[10];
    int day;

    printf("\nEnter employee DNI:");
    scanf("%10s", DNI);

    // Comprobar que sea exactamente 9 digitos o volver a pedir DNI

    printf("\nEnter day of the month:");
    scanf("%d", &day);

    if (day < 1 || day > 31) {
        printf("Invalid day.\n");
        return;
    }

    for (int i = 0; i < *currentEmployees; i++) {
        if (strcmp(company[i].DNI, DNI) == 0) {
            int hour, min;
            Get_time(&hour, &min);

            *(hourEntry) = hour;
            *(minEntry) = min;

            printf("[+] Entry time recorded for %s - day %d %d:%dh\n", DNI, day,  *(hourEntry), *(minEntry));
            return;
        }
    }
    printf("Employee with DNI %s not found.\n", DNI);

}


// Option 3, Record Exit Time

void recordExitEmployee(Employee company[], int size, int *currentEmployees, int *hourExit, int*minExit, int *hourEntry, int *minEntry, int (*hoursMonthEmployees)[31]) {
    char DNI[10];
    int day, hour, min;
    int hoursWorked;
    int minsWorked;

    printf("\nEnter employee DNI: ");
    scanf("%10s", DNI);

    printf("\nEnter day of the month: ");
    scanf("%d", &day);

    if (day < 1 || day > 31) {
        printf("Invalid day.\n");
        return;
    }

    for (int i = 0; i < *currentEmployees; i++) {
        if (strcmp(company[i].DNI, DNI) == 0) {
            printf("Enter 1 for manual input OR enter 2 for system time: ");
            int choice;
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Enter exit hour (HH MM): ");
                scanf("%d %d", &hour, &min);

                if ((hour < *(hourEntry)) ||
                    (hour == *(hourEntry) &&
                     min == *(minEntry)) || (hour > 19 || (hour == 19 && min > 0))) {
                    printf("Invalid exit time.\n");
                    return;
                }
            } else {
                Get_time(&hour, &min);
            }
            *(hourExit) = hour;
            *(minExit) = min;

            hoursWorked = *(hourExit) - *(hourEntry);
            minsWorked = *(minExit) - *(minEntry);
            if (minsWorked < 0) {
                hoursWorked--;
                minsWorked += 60;
            }

            printf("Hours worked on day %d: %d hours and %d minutes\n", day ,hoursWorked, minsWorked);

            company[i].monthlyHours += hoursWorked;
            (*hoursMonthEmployees)[day-1] = hoursWorked;
            //hoursMonthEmployee[i][day-1] = hoursWorked;

            return;
        }

    }

    printf("Employee with DNI %s not found", DNI);

}

// Option 4, Calculate Monthly Salary

void calculateMonthlySalary(Employee company[], int size, int *(currentEmployees)) {

    for (int i = 0; i < *(currentEmployees); i++) {

        if (company[i].monthlyHours > 145){
            company[i].hourlyRate = 15;
        }else if(company[i].monthlyHours <= 145 && company[i].monthlyHours >= 136){
            company[i].hourlyRate = 14;
        }else if(company[i].monthlyHours <= 135 && company[i].monthlyHours >= 120){
            company[i].hourlyRate = 12.45;
        } else {
            company[i].hourlyRate = 8;
        }

        float monthlySalary = company[i].monthlyHours * company[i].hourlyRate;

        company[i].monthlySalary = monthlySalary;
        printf("Employee DNI: %s, Name: %s, Monthly Salary: %.2f\n", company[i].DNI, company[i].name, monthlySalary);
    }

}

// Option 5, Remove An Employee

void removeEmployee(Employee company[], int size, int *currentEmployees) {
    char DNI[10];
    printf("\nEnter employee's DNI to remove: ");
    scanf("%10s", DNI);

    int index = FindEmployeeIndex(company, size, DNI, currentEmployees);

    if (index != -1) {
        for (int i = index; i < *currentEmployees - 1; i++) {
            company[i] = company[i + 1];
        }
        (*currentEmployees)--;
        printf("Employee with DNI %s has been removed.\n", DNI);
    } else {
        printf("Employee with DNI %s not found.\n", DNI);
    }
}


// Aux Function Search Employee
int FindEmployeeIndex(Employee company[], int size,char* DNI, int *(currentEmployees)) {
    for (int i = 0; i < *(currentEmployees); i++) {
        if (strcmp(company[i].DNI, DNI) == 0) {
            return i;
        }
    }
    return -1;
}

void printMatriz(int (*hoursMonthEmployees)[31]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 31; j++) {
            printf("Day: %d, Employee: %d, Worked hours: %d\n", j + 1, i + 1, hoursMonthEmployees[i][j]);
        }
        printf("\n\n");
    }
}

void printArray(Employee company, int size, int *(currentEmployees)){

    for (int i = 0; i < *(currentEmployees); i++) {
        printf("\nEmployee %d\n",i);
        printf("\nName: %s\n", company.name);
        printf("\nName: %s\n", company.lastName);
        printf("\nName: %s\n", company.DNI);
        printf("\nName: %f\n", company.hourlyRate);
        printf("\nName: %d\n", company.workedTime);
        printf("\nName: %f\n", company.monthlySalary);
        printf("\n---------------------\n");
    }

}