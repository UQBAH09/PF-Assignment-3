#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPLOYEE_COUNT 4 // Define the number of employees

// Define the structure for Employee details
struct Employee
{
    int employeeCode;
    char employeeName[50];
    int dateOfJoining; // Format: DDMMYYYY
};

// Function to input employee details
void inputEmployeeDetails(struct Employee employees[], int index)
{
    char name[50];
    printf("\nEmployee %d\n", index + 1);

    printf("Enter employee code: ");
    scanf("%d", &employees[index].employeeCode);
    getchar();

    printf("Enter employee name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    strcpy(employees[index].employeeName, name);

    printf("Enter date of joining (DDMMYYYY): ");
    scanf("%d", &employees[index].dateOfJoining);
    getchar();
}

// Function to calculate the total number of days since year 0 (approximation)
int calculateTotalDays(int date)
{
    int day = date / 1000000;
    int month = (date / 10000) % 100;
    int year = date % 10000;
    return day + (month * 30) + (year * 365);
}

// Function to find and display employees with tenure over 3 years
void findLongTenureEmployees(struct Employee employees[])
{
    int currentDate, eligibleEmployeeCount = 0;

    printf("\nEnter current date (DDMMYYYY): ");
    scanf("%d", &currentDate);

    int currentTotalDays = calculateTotalDays(currentDate);

    printf("\nEmployees with tenure of more than 3 years:\n");
    for (int i = 0; i < EMPLOYEE_COUNT; i++)
    {
        int joiningTotalDays = calculateTotalDays(employees[i].dateOfJoining);
        int tenureDays = currentTotalDays - joiningTotalDays;

        if (tenureDays >= 365 * 3)
        {
            printf("Employee ID: %d, Employee Name: %s\n", employees[i].employeeCode, employees[i].employeeName);
            eligibleEmployeeCount++;
        }
    }

    printf("\nTotal employees with tenure more than 3 years: %d\n", eligibleEmployeeCount);
}

int main(void)
{
    struct Employee employees[EMPLOYEE_COUNT];

    // Input details for all employees
    for (int i = 0; i < EMPLOYEE_COUNT; i++)
    {
        inputEmployeeDetails(employees, i);
    }

    // Find and display employees with tenure over 3 years
    findLongTenureEmployees(employees);

    return 0;
}