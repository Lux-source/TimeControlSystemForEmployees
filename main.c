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


/*typedef struct {
    int hourEntry;
    int minEntry;
    int hourExit;
    int minExit;
} DailyHours;*/


typedef struct {
    char name[20];
    char lastName[20];
    char DNI[10]; // last char is '\0'
    int monthlyHours;
    int yearlyHours;
    float hourlyRate;
    int workedTime;
} Employee;

// Headers



void registerEmployee(Employee company[], int size, int *currentEmployees);

void recordEntryEmployee(Employee company[], int size, int *currentEmployees, int *hourEntry, int *minEntry);

void recordExitEmployee(Employee company[], int size, int *currentEmployees, int *hourExit, int*minExit, int *hourEntry, int *minEntry);

int main() {

    int hour = -1;
    int min = -1;
    int option = -1;
    Get_time(&hour, &min);
    int entryHour;
    int entryMin;
    int exitHour;
    int exitMin;

    int hoursMonthEmployees[31][20] = {0};

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
                recordExitEmployee(company,20,&currentEmployees, &exitHour, &exitMin, &entryHour, &entryMin);
                printf("\n");
                break;
            case 4:
                break;
            case 5:
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

void recordExitEmployee(Employee company[], int size, int *currentEmployees, int *hourExit, int*minExit, int *hourEntry, int *minEntry) {
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

            printf("Hours worked on day %d: %d hours and %d minutes\n", hoursWorked, minsWorked);

            company[i].monthlyHours += hoursWorked;
            return;
        }

    }

    printf("Employee with DNI %s not found", DNI);

}

// Option 4, Calculate Monthly Salary

// Option 5, Remove An Employee

void removeEmployee(){}

// Option 6, Exit The Program

// Aux Function Search Employee
int FindEmployeeIndex(Employee company[], int size,char* DNI, int *(currentEmployees)) {
    for (int i = 0; i < *(currentEmployees); i++) {
        if (strcmp(company[i].DNI, DNI) == 0) {
            return i;
        }
    }
    return -1;
}