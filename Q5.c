#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to initialize inventory
void initializeInventory(char ****Supplies, int **numSupplies, int numSpecies) {
    *Supplies = (char ***)malloc(numSpecies * sizeof(char **));
    *numSupplies = (int *)malloc(numSpecies * sizeof(int));
    if (*Supplies == NULL || *numSupplies == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < numSpecies; i++) {
        (*Supplies)[i] = NULL;  // Initialize supplies as NULL
        (*numSupplies)[i] = 0;  // Initialize number of supplies to 0
    }
}

// Function to add supplies for each species
void addSupplies(char ***Supplies, int *numSupplies, int speciesIndex) {
    printf("Enter number of supplies for species %d: ", speciesIndex + 1);
    scanf("%d", &numSupplies[speciesIndex]);
    getchar(); // Consume newline character left in the input buffer

    Supplies[speciesIndex] = (char **)malloc(numSupplies[speciesIndex] * sizeof(char *));
    if (Supplies[speciesIndex] == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < numSupplies[speciesIndex]; i++) {
        char item[100];
        printf("Enter supply %d: ", i + 1);
        fgets(item, sizeof(item), stdin);
        item[strcspn(item, "\n")] = '\0'; // Remove newline character

        Supplies[speciesIndex][i] = (char *)malloc((strlen(item) + 1) * sizeof(char));
        if (Supplies[speciesIndex][i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        strcpy(Supplies[speciesIndex][i], item);
    }
}

// Function to update a supply
void updateSupply(char ***Supplies, int *numSupplies, int speciesIndex) {
    if (numSupplies[speciesIndex] == 0) {
        printf("No supplies to update for this species.\n");
        return;
    }

    int supplyIndex;
    printf("Enter the supply number to update (1 to %d): ", numSupplies[speciesIndex]);
    scanf("%d", &supplyIndex);
    getchar(); // Consume newline character left by scanf

    if (supplyIndex < 1 || supplyIndex > numSupplies[speciesIndex]) {
        printf("Invalid supply number.\n");
        return;
    }

    supplyIndex--; // Convert to 0-based index
    printf("Enter the new name for supply %d: ", supplyIndex + 1);
    char newSupply[100];
    fgets(newSupply, sizeof(newSupply), stdin);
    newSupply[strcspn(newSupply, "\n")] = '\0'; // Remove newline character

    // Free old supply memory and allocate new memory for the updated name
    free(Supplies[speciesIndex][supplyIndex]);
    Supplies[speciesIndex][supplyIndex] = (char *)malloc((strlen(newSupply) + 1) * sizeof(char));
    if (Supplies[speciesIndex][supplyIndex] == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(Supplies[speciesIndex][supplyIndex], newSupply);

    printf("Supply %d updated successfully.\n", supplyIndex + 1);
}

// Function to display inventory
void displayInventory(char ***Supplies, char Species[][50], int *numSupplies, int numSpecies) {
    printf("\nInventory:\n");
    for (int i = 0; i < numSpecies; i++) {
        printf("Species: %s\n", Species[i]);
        for (int j = 0; j < numSupplies[i]; j++) {
            printf("  Supply %d: %s\n", j + 1, Supplies[i][j]);
        }
    }
}

// Function to free all memory for supplies
void freeInventory(char ***Supplies, int *numSupplies, int numSpecies) {
    for (int i = 0; i < numSpecies; i++) {
        for (int j = 0; j < numSupplies[i]; j++) {
            free(Supplies[i][j]);
        }
        free(Supplies[i]);
    }
    free(Supplies);
    free(numSupplies);
}

int main() {
    int numSpecies;
    printf("Enter number of species: ");
    scanf("%d", &numSpecies);
    getchar(); // Consume newline character left by scanf

    char Species[numSpecies][50];
    for (int i = 0; i < numSpecies; i++) {
        printf("Enter name of species %d: ", i + 1);
        fgets(Species[i], sizeof(Species[i]), stdin);
        Species[i][strcspn(Species[i], "\n")] = '\0'; // Remove newline character
    }

    char ***Supplies;
    int *numSupplies;
    initializeInventory(&Supplies, &numSupplies, numSpecies);

    for (int i = 0; i < numSpecies; i++) {
        addSupplies(Supplies, numSupplies, i);
    }

    int choice, speciesIndex;
    do {
        printf("\nMenu:\n");
        printf("1. Display Inventory\n");
        printf("2. Update Supply\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayInventory(Supplies, Species, numSupplies, numSpecies);
                break;
            case 2:
                printf("Enter the species number to update (1 to %d): ", numSpecies);
                scanf("%d", &speciesIndex);
                getchar(); // Consume newline character left by scanf

                if (speciesIndex < 1 || speciesIndex > numSpecies) {
                    printf("Invalid species number.\n");
                } else {
                    updateSupply(Supplies, numSupplies, speciesIndex - 1);
                }
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    freeInventory(Supplies, numSupplies, numSpecies);

    return 0;
}