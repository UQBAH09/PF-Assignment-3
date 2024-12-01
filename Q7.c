#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Content Metadata structure
typedef struct {
    char title[100];
    float rating;
    int runtime;  // In minutes
    char encoding_format[20];
} ContentMetadata;

// Device Preferences structure
typedef struct {
    char resolution[20];
    int playback_history[100]; // Stores IDs of played content
    int playback_count;
    float bandwidth_usage; // In Mbps
} DevicePreference;

// User Profile structure
typedef struct {
    double *engagementRow;       // Pointer to the user's row in engagementMatrix
    DevicePreference **devices; // Pointer to the user's device preferences
} UserProfile;

// Function to create the Engagement Matrix (2D array)
double **createEngagementMatrix(int num_users, int num_categories) {
    double **matrix = (double **)malloc(num_users * sizeof(double *));
    for (int i = 0; i < num_users; i++) {
        matrix[i] = (double *)malloc(num_categories * sizeof(double));
        for (int j = 0; j < num_categories; j++) {
            matrix[i][j] = 0.0; // Initialize engagement scores to 0
        }
    }
    return matrix;
}

// Function to create the Device Preferences Matrix (2D array)
DevicePreference ***createDeviceMatrix(int num_users, int num_devices) {
    DevicePreference ***matrix = (DevicePreference ***)malloc(num_users * sizeof(DevicePreference **));
    for (int i = 0; i < num_users; i++) {
        matrix[i] = (DevicePreference **)malloc(num_devices * sizeof(DevicePreference *));
        for (int j = 0; j < num_devices; j++) {
            matrix[i][j] = (DevicePreference *)malloc(sizeof(DevicePreference));
            strcpy(matrix[i][j]->resolution, "1080p"); // Default resolution
            matrix[i][j]->playback_count = 0;         // Initialize playback count
            matrix[i][j]->bandwidth_usage = 0.0;      // Initialize bandwidth usage
        }
    }
    return matrix;
}

// Function to create the Content Metadata Matrix (2D array)
ContentMetadata ***createContentMetadataMatrix(int num_categories, int num_content_per_category) {
    ContentMetadata ***matrix = (ContentMetadata ***)malloc(num_categories * sizeof(ContentMetadata **));
    for (int i = 0; i < num_categories; i++) {
        matrix[i] = (ContentMetadata **)malloc(num_content_per_category * sizeof(ContentMetadata *));
        for (int j = 0; j < num_content_per_category; j++) {
            matrix[i][j] = (ContentMetadata *)malloc(sizeof(ContentMetadata));
            strcpy(matrix[i][j]->title, "Default Title");
            matrix[i][j]->rating = 0.0; // Default rating
            matrix[i][j]->runtime = 0;  // Default runtime
            strcpy(matrix[i][j]->encoding_format, "H.264");
        }
    }
    return matrix;
}

// Function to create user profiles
UserProfile *createUserProfiles(int num_users, double **engagementMatrix, DevicePreference ***deviceMatrix, int num_devices) {
    UserProfile *users = (UserProfile *)malloc(num_users * sizeof(UserProfile));
    for (int i = 0; i < num_users; i++) {
        users[i].engagementRow = engagementMatrix[i];  // Link user's engagement row
        users[i].devices = deviceMatrix[i];           // Link user's devices
    }
    return users;
}

int main() {
    int num_users = 3;
    int num_categories = 5;
    int num_devices = 2;
    int num_content_per_category = 4;

    // Create Engagement Matrix
    double **engagementMatrix = createEngagementMatrix(num_users, num_categories);

    // Create Device Preferences Matrix
    DevicePreference ***deviceMatrix = createDeviceMatrix(num_users, num_devices);

    // Create Content Metadata Matrix
    ContentMetadata ***contentMetadataMatrix = createContentMetadataMatrix(num_categories, num_content_per_category);

    // Create User Profiles
    UserProfile *userProfiles = createUserProfiles(num_users, engagementMatrix, deviceMatrix, num_devices);

    // Update an engagement score
    engagementMatrix[0][2] = 75.5; // User 0, Category 2

    // Update device preferences
    strcpy(deviceMatrix[1][0]->resolution, "4K");
    deviceMatrix[1][0]->bandwidth_usage = 25.3; // User 1, Device 0

    // Update content metadata
    strcpy(contentMetadataMatrix[3][1]->title, "Inception");
    contentMetadataMatrix[3][1]->rating = 8.8;
    contentMetadataMatrix[3][1]->runtime = 148;

    // Print example data
    printf("User 0's Engagement Score for Category 2: %.2f\n", engagementMatrix[0][2]);
    printf("User 1's Device 0 Resolution: %s\n", deviceMatrix[1][0]->resolution);
    printf("User 1's Device 0 Bandwidth Usage: %.2f Mbps\n", deviceMatrix[1][0]->bandwidth_usage);
    printf("Category 3, Content 1: %s, Rating: %.1f, Runtime: %d minutes\n",
           contentMetadataMatrix[3][1]->title,
           contentMetadataMatrix[3][1]->rating,
           contentMetadataMatrix[3][1]->runtime);

    // Free allocated memory (to avoid memory leaks)
    for (int i = 0; i < num_users; i++) {
        free(engagementMatrix[i]);
        for (int j = 0; j < num_devices; j++) {
            free(deviceMatrix[i][j]);
        }
        free(deviceMatrix[i]);
    }
    for (int i = 0; i < num_categories; i++) {
        for (int j = 0; j < num_content_per_category; j++) {
            free(contentMetadataMatrix[i][j]);
        }
        free(contentMetadataMatrix[i]);
    }
    free(engagementMatrix);
    free(deviceMatrix);
    free(contentMetadataMatrix);
    free(userProfiles);

    return 0;
}
