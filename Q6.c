#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Weather Forecast structure
typedef struct
{
    float temperature;
    float rainfall;
    float wind_speed;
} WeatherForecast;

// Define Crop structure
typedef struct
{
    char crop_type[50];
    int growth_stage;
    float expected_yield;
    WeatherForecast *weather; // Pointer to WeatherForecast structure
} Crop;

// Define Equipment structure
typedef struct
{
    char equipment_name[50];
    int operational_status; // 1 for active, 0 for inactive
    float fuel_level;
    char activity_schedule[100];
} Equipment;

// Define Sensor structure
typedef struct
{
    float soil_nutrients;
    float pH_level;
    float pest_activity;
} Sensor;

// Define Field structure
typedef struct
{
    float gps_latitude;
    float gps_longitude;
    float soil_health_metric;
    float moisture_level;
    Crop *crops;          // Pointer to array of Crop structures
    Equipment *equipment; // Pointer to array of Equipment structures
    Sensor *sensors;      // Pointer to array of Sensor structures
    int num_crops;
    int num_equipment;
    int num_sensors;
} Field;

// Define Regional Hub structure
typedef struct
{
    Field *fields; // Pointer to array of Field structures
    int num_fields;
    float aggregate_yield_prediction;
    char resource_distribution[100];
    char emergency_response_plan[100];
} RegionalHub;

// Define Central Analytics Server structure
typedef struct
{
    RegionalHub *hubs; // Pointer to array of RegionalHub structures
    int num_hubs;
} AnalyticsServer;

// Function to create a field
Field *create_field(int num_crops, int num_equipment, int num_sensors)
{
    Field *field = (Field *)malloc(sizeof(Field));
    field->crops = (Crop *)malloc(num_crops * sizeof(Crop));
    field->equipment = (Equipment *)malloc(num_equipment * sizeof(Equipment));
    field->sensors = (Sensor *)malloc(num_sensors * sizeof(Sensor));
    field->num_crops = num_crops;
    field->num_equipment = num_equipment;
    field->num_sensors = num_sensors;
    return field;
}

// Function to create a regional hub
RegionalHub *create_regional_hub(int num_fields)
{
    RegionalHub *hub = (RegionalHub *)malloc(sizeof(RegionalHub));
    hub->fields = (Field *)malloc(num_fields * sizeof(Field));
    hub->num_fields = num_fields;
    return hub;
}

// Function to create the analytics server
AnalyticsServer *create_analytics_server(int num_hubs)
{
    AnalyticsServer *server = (AnalyticsServer *)malloc(sizeof(AnalyticsServer));
    server->hubs = (RegionalHub *)malloc(num_hubs * sizeof(RegionalHub));
    server->num_hubs = num_hubs;
    return server;
}

// Function to initialize a sample system
void initialize_sample_system()
{
    // Create a sample analytics server with 1 hub
    AnalyticsServer *server = create_analytics_server(1);

    // Initialize 1 hub with 2 fields
    server->hubs[0] = *create_regional_hub(2);

    // Initialize fields
    for (int i = 0; i < 2; i++)
    {
        server->hubs[0].fields[i] = *create_field(3, 2, 5); // 3 crops, 2 equipment, 5 sensors
        Field *field = &server->hubs[0].fields[i];

        // Populate crop data
        for (int j = 0; j < field->num_crops; j++)
        {
            strcpy(field->crops[j].crop_type, "Wheat");
            field->crops[j].growth_stage = j + 1;
            field->crops[j].expected_yield = 100 + j * 10;
            field->crops[j].weather = (WeatherForecast *)malloc(sizeof(WeatherForecast));
            field->crops[j].weather->temperature = 25.5 + j;
            field->crops[j].weather->rainfall = 100 - j * 5;
            field->crops[j].weather->wind_speed = 10 + j;
        }

        // Populate equipment data
        for (int j = 0; j < field->num_equipment; j++)
        {
            strcpy(field->equipment[j].equipment_name, "Tractor");
            field->equipment[j].operational_status = 1;
            field->equipment[j].fuel_level = 50.0 + j * 10;
            strcpy(field->equipment[j].activity_schedule, "Daily tilling");
        }

        // Populate sensor data
        for (int j = 0; j < field->num_sensors; j++)
        {
            field->sensors[j].soil_nutrients = 80.0 + j;
            field->sensors[j].pH_level = 6.5 + j * 0.1;
            field->sensors[j].pest_activity = j * 2;
        }
    }

    printf("System initialized successfully.\n");

    // Example: Printing some data to verify
    printf("Hub 0, Field 0, Crop 0: %s, Growth Stage: %d, Yield: %.2f\n",
           server->hubs[0].fields[0].crops[0].crop_type,
           server->hubs[0].fields[0].crops[0].growth_stage,
           server->hubs[0].fields[0].crops[0].expected_yield);

    // Free allocated memory (important in real applications)
    for (int i = 0; i < 2; i++)
    {
        Field *field = &server->hubs[0].fields[i];
        for (int j = 0; j < field->num_crops; j++)
        {
            free(field->crops[j].weather);
        }
        free(field->crops);
        free(field->equipment);
        free(field->sensors);
    }
    free(server->hubs[0].fields);
    free(server->hubs);
    free(server);
}

int main()
{
    initialize_sample_system();
    return 0;
}
