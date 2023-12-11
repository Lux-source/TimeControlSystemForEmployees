//
// Created by andre on 20/11/2023.
//
// Group Number 10
//
// Members: ALONSO GARDE ALITE, LUCIAN ANDREI NEGOITA, HECTOR RUIZ LOPEZ
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
    int remainMins; // Minutes remaining used for getting the remaining hours not counted
    int yearlyHours;
    float hourlyRate;
    float monthlySalary;
    int workedTime;
} Employee;

// Headers

void registerEmployee(Employee *company,int *currentEmployees); // REGISTER EMPLOYEE (OPTION 1)

void recordEntryEmployee(Employee *company, int *currentEmployees, int *hourEntry, int *minEntry); // RECORD ENTRY (OPTION 2)

void
recordExitEmployee(Employee *company, int *currentEmployees, int *hourExit, int *minExit, int *hourEntry,
                   int *minEntry, int hoursMonthlyEmployees[20][31]); // RECORD EXIT EMPLOYEE (OPTION 3)

int FindEmployeeIndex(Employee *company, char *DNI, int *currentEmployees); // AUXILIARY OPERATION FOR USING WHEN REMOVING THE EMPLOYEE

void calculateMonthlySalary(Employee *company, int *(currentEmployees)); // CALCULATE SALARY OF THE MONTH (OPTION 4)

void removeEmployee(Employee *company,int *currentEmployees); // REMOVE EMPLOYEE (OPTION 5)

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
                registerEmployee(company, &currentEmployees);
                printf("\n");
                break;
            case 2:
                printf("\n");
                recordEntryEmployee(company, &currentEmployees, &entryHour, &entryMin);
                printf("\n");
                break;
            case 3:
                printf("\n");
                recordExitEmployee(company, &currentEmployees, &exitHour, &exitMin, &entryHour, &entryMin,
                                   hoursMonthEmployees);
                printf("\n");
                break;
            case 4:
                printf("\n");
                calculateMonthlySalary(company, &currentEmployees);
                printf("\n");
                break;
            case 5:
                printf("\n");
                removeEmployee(company, &currentEmployees);
                printf("\n");
                break;
            case 6:
                printf("\nBye!"); // EXIT PROGRAM (FINAL OPTION)
                break;
            default:
                printf("\n\nTry again, option not valid!");
        }
    } while (option != 6);


    return 0;
}




// Option 1, Register New Employee

void registerEmployee(Employee *company, int *currentEmployees) {

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

void recordEntryEmployee(Employee *company, int *currentEmployees, int *hourEntry, int *minEntry) {
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

            printf("[+] Entry time recorded for %s - day %02d, %02d:%02dh\n", DNI, day, *(hourEntry), *(minEntry));
            return;
        }
    }
    printf("Employee with DNI %s not found.\n", DNI);

}


// Option 3, Record Exit Time

void
recordExitEmployee(Employee *company, int *currentEmployees, int *hourExit, int *minExit, int *hourEntry,
                   int *minEntry, int hoursMonthlyEmployees[20][31]) {
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
                do {
                    printf("Enter exit hour (HH MM): ");
                    scanf("%d %d", &hour, &min);
                    if ((hour < 0 || hour > 23 || min < 0 || min > 59) || // Invalid hours
                        (hour < *(hourEntry) || (hour == *(hourEntry) && min < *(minEntry))) ||
                        // Exit hour is prev to entry
                        (hour > 19 || (hour == 19 && min > 0))) { // Hour past 19:00
                        printf("Invalid exit time.\n");
                    }
                } while ((hour < 0 || hour > 23 || min < 0 || min > 59) ||
                         (hour < *(hourEntry) || (hour == *(hourEntry) && min < *(minEntry))) ||
                         (hour > 19 || (hour == 19 && min > 0)));
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

            printf("Hours worked on day %d: %d hours and %d minutes\n", day, hoursWorked, minsWorked);

            company[i].monthlyHours += hoursWorked;
            hoursMonthlyEmployees[i][day - 1] = hoursWorked;
            company[i].remainMins += minsWorked; // To take into account remaining minutes
            return;
        }

    }

    printf("Employee with DNI %s not found", DNI);

}

// Option 4, Calculate Monthly Salary

void calculateMonthlySalary(Employee *company, int *(currentEmployees)) {

    int extraHours = 0;

    for (int i = 0; i < *(currentEmployees); i++) {


        // In case we have sufficient extra minutes, convert them to hours and update counter of remaining
        if (company[i].remainMins > 59){
            extraHours = company[i].remainMins / 60;
            company[i].remainMins = company[i].remainMins % 60;
            company[i].monthlyHours += extraHours;
        }
        // Check how much are we going to pay given the hours worked on this month
        if (company[i].monthlyHours > 145) {
            company[i].hourlyRate = 15;
        } else if (company[i].monthlyHours <= 145 && company[i].monthlyHours >= 136) {
            company[i].hourlyRate = 14;
        } else if (company[i].monthlyHours <= 135 && company[i].monthlyHours >= 120) {
            company[i].hourlyRate = 12.45;
        } else {
            company[i].hourlyRate = 8;
        }

        company[i].monthlySalary = (float)company[i].monthlyHours * company[i].hourlyRate;

        company[i].yearlyHours += company[i].monthlyHours; // In order to be able to calculate yearly salary, accumulate the monthly hours

        printf("Employee DNI: %s, Name: %s, Surname: %s, Monthly Salary: %.2f\n", company[i].DNI, company[i].name, company[i].lastName, company[i].monthlySalary);
    }

}

// Option 5, Remove An Employee

void removeEmployee(Employee *company, int *currentEmployees) {
    char DNI[10];
    printf("\nEnter employee's DNI to remove: ");
    scanf("%10s", DNI);

    int index = FindEmployeeIndex(company, DNI, currentEmployees);
    // after finding the employee turn the hourly rate to 8 and calculate compensation
    company[index].hourlyRate = 8;
    company[index].monthlySalary= (float)company[index].monthlyHours*company[index].hourlyRate;
    company[index].monthlySalary= company[index].monthlySalary*1.03;

    if (index != -1) {
        for (int i = index; i < *currentEmployees - 1; i++) {
            company[i] = company[i + 1];
        }
        (*currentEmployees)--;
        printf("Employee with DNI %s has been removed and will be paid %.2f.\n", DNI, company[index].monthlySalary);
    } else {
        printf("Employee with DNI %s not found.\n", DNI);
    }
}


// Aux Function Search Employee
int FindEmployeeIndex(Employee *company, char *DNI, int *(currentEmployees)) {
    for (int i = 0; i < *(currentEmployees); i++) {
        if (strcmp(company[i].DNI, DNI) == 0) {
            return i;

        }
    }
    return -1;
}
