//
// Created by andre on 20/11/2023.
//
// Group Number 10
//
// Members: ALONSO GARDE ALITE, LUCIAN ANDREI NEGOITA, HÉCTOR RUÍZ LÓPEZ
//
#include "library.h"
#include<time.h>
#include <stdio.h>
#include <string.h>

// Structs



typedef struct {
    int hourEntry;
    int minEntry;
    int hourExit;
    int minExit;
} DailyHours;

typedef struct {
    char name[20];
    char lastName[20];
    char DNI[9];
    int monthlyHours;
    int yearlyHours;
    float hourlyRate;
    DailyHours workedTime[31];
} Employee;

// Headers



void registerEmployee(Employee company[], int size, int currentEmployees);

int main() {

    int hour = -1;
    int min = -1;
    int option = -1;
    Get_time(&hour, &min);

    Employee company[20];

    //printf("Time is: %d:%d", hour, min);

    do {

        printf("\n\n1. Register a new employee.");
        printf("\n2. Record entry time.");
        printf("\n3. Record exit time.");
        printf("\n4. Calculate monthly salary.");
        printf("\n5. Remove an employee.");
        printf("\n6. Exit the program.");

        printf("\n");

        scanf(" %d", &option);

        switch (option) {
            case 1:
                printf("\n");
                registerEmployee(company,20,5);
                printf("\n");
                break;
            case 2:
                printf("\n");
                printf("Getting Entry Time...:");
                //Get_time();
                printf("\n");
                break;
            case 3:
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

void registerEmployee(Employee company[], int size, int currentEmployees){

    printf("\nEnter name: ");
    scanf("%s", company->name);


}

// Option 2, Record Entry Time

// Option 3, Record Exit Time

// Option 4, Calculate Monthly Salary

// Option 5, Remove An Employee

// Option 6, Exit The Program