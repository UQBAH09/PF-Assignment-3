#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee
{
    int *ratings;
    int totalScore;
};

void inputEmployees(int **ratings, int numEmployees, int numPeriods)
{
    *ratings = (int *)malloc(numEmployees * numPeriods * sizeof(int));
    if (*ratings == NULL) {
        printf("Memory allocation failed!\n");
        exit(1); // Exit if memory allocation fails
    }

    int rating;
    for (int i = 0; i < numEmployees; i++)
    {
        for (int j = 0; j < numPeriods; j++)
        {
            printf("Enter ratings for Employee %d:\n", i + 1);
            rating = 0;
            do
            {
                printf("Enter rating for period %d (1-10): ", j + 1);
                scanf("%d", &rating);
                
                if (rating < 1 || rating > 10)
                {
                    printf("Invalid rating. Please enter a rating between 1 and 10.\n");
                }
            } while (rating < 1 || rating > 10);

            (*ratings)[i * numPeriods + j] = rating;
        }
    }
}

void displayPerformance(int **ratings, int numEmployees, int numPeriods)
{
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < numEmployees; i++)
    {
        printf("Employee %d:\n", i + 1);
        for (int j = 0; j < numPeriods; j++)
        {
            printf("Period %d: %d\n", j + 1, (*ratings)[i * numPeriods + j]);
        }
        printf("------------------------------------------------------------\n");
    }
}

int findEmployeeOfTheYear(int **ratings, int numEmployees, int numPeriods)
{
    float avgRating[numEmployees];

    for (int i = 0; i < numEmployees; i++)
    {
        avgRating[i] = 0;
        for (int j = 0; j < numPeriods; j++)
        {
            avgRating[i] += (*ratings)[i * numPeriods + j];
        }
        avgRating[i] /= numPeriods;
    }

    int index = 0;
    for (int i = 0; i < numEmployees; i++)
    {
        if (avgRating[index] < avgRating[i])
        {
            index = i;
        }
    }
    return index;
}

int findHighestRatedPeriod(int **ratings, int numEmployees, int numPeriods)
{
    float avgRating[numPeriods];

    for (int i = 0; i < numPeriods; i++)
    {
        avgRating[i] = 0;
        for (int j = 0; j < numEmployees; j++)
        {
            avgRating[i] += (*ratings)[i * numEmployees + j];
        }
        avgRating[i] /= numEmployees;
    }

    int index = 0;
    for (int i = 0; i < numPeriods; i++)
    {
        if (avgRating[index] < avgRating[i])
        {
            index = i;
        }
    }
    return index;
}

int findWorstPerformingEmployee(int **ratings, int numEmployees, int numPeriods)
{
    float avgRating[numEmployees];

    for (int i = 0; i < numEmployees; i++)
    {
        avgRating[i] = 0;
        for (int j = 0; j < numPeriods; j++)
        {
            avgRating[i] += (*ratings)[i * numPeriods + j];
        }
        avgRating[i] /= numPeriods;
    }

    int index = 0;
    for (int i = 0; i < numEmployees; i++)
    {
        if (avgRating[index] > avgRating[i])
        {
            index = i;
        }
    }
    return index;
}

int main(void) {
    int numEmployees, numPeriods;
    int* ratings = NULL;

    // Input number of employees and evaluation periods
    printf("Enter the number of employees: ");
    scanf("%d", &numEmployees);
    printf("Enter the number of evaluation periods: ");
    scanf("%d", &numPeriods);

    // Input ratings for employees
    inputEmployees(&ratings, numEmployees, numPeriods);

    // Display performance ratings for all employees
    displayPerformance(&ratings, numEmployees, numPeriods);

    // Find Employee of the Year
    int employeeOfTheYear = findEmployeeOfTheYear(&ratings, numEmployees, numPeriods);
    printf("Employee of the Year: Employee %d\n", employeeOfTheYear + 1);

    // Find Highest Rated Period
    int highestRatedPeriod = findHighestRatedPeriod(&ratings, numEmployees, numPeriods);
    printf("Highest Rated Period: Period %d\n", highestRatedPeriod + 1);

    // Find Worst Performing Employee
    int worstPerformingEmployee = findWorstPerformingEmployee(&ratings, numEmployees, numPeriods);
    printf("Worst Performing Employee: Employee %d\n", worstPerformingEmployee + 1);

    // Free dynamically allocated memory
    free(ratings);

    return 0;
}