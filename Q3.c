#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to validate the email address
int validateEmail(const char email[])
{
    int atCount = 0;
    char *atPtr;

    // Check if the email is not empty
    if (email == NULL || strlen(email) == 0)
    {
        return 0;
    }

    // Find the '@' character in the email
    atPtr = strchr(email, '@');

    // If '@' is not found, the email is invalid
    if (!atPtr)
    {
        return 0;
    }

    // Count the number of '@' symbols
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            atCount++;
        }
    }

    // Valid if there is exactly one '@' and a '.' after '@'
    if (atCount == 1 && strchr(atPtr, '.') != NULL)
    {
        return 1;
    }

    return 0;
}

int main(void)
{
    char *email;
    int maxLength;

    printf("Enter maximum length of the email: ");
    scanf("%d", &maxLength);
    getchar();

    // Allocate memory for the email input
    email = (char *)malloc((maxLength + 1) * sizeof(char));
    if (!email)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the email address: ");
    fgets(email, maxLength + 1, stdin);
    email[strcspn(email, "\n")] = '\0';

    if (validateEmail(email) == 1)
    {
        printf("Email is valid.\n");
    }
    else
    {
        printf("Email is invalid.\n");
    }

    free(email);

    return 0;
}
