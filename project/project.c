#include <stdio.h>

// Enumerations for states
enum EngineState {
    ENGINE_OFF,
    ENGINE_ON
};

enum ACState {
    AC_OFF,
    AC_ON
};

enum EngineTempControllerState {
    CONTROLLER_OFF,
    CONTROLLER_ON
};

// Function prototypes
void displayMenu();
void displaySensorsMenu();
void displayVehicleState(enum EngineState engineState, enum ACState acState, int speed, int roomTemp, int engineTemp, enum EngineTempControllerState controllerState);

// Macros
#define WITH_ENGINE_TEMP_CONTROLLER 1

int main() {
    char input;
    enum EngineState engineState = ENGINE_OFF;
    enum ACState acState = AC_OFF;
    int speed = 100;
    int roomTemp = 35;
    int engineTemp = 90;
    enum EngineTempControllerState engineTempControllerState = CONTROLLER_OFF;

    do {
        displayMenu();
        scanf(" %c", &input);

        switch (input) {
            case 'a': // Turn on the vehicle engine
                engineState = ENGINE_ON;

                while (engineState == ENGINE_ON) {
                    // Display the current vehicle state
                    displayVehicleState(engineState, acState, speed, roomTemp, engineTemp, engineTempControllerState);

                    displaySensorsMenu(); // Display set menu after displaying the current state

                    char sensorInput;
                    scanf(" %c", &sensorInput);

                    switch (sensorInput) {
                        case 'a': // Turn off the engine
                            engineState = ENGINE_OFF;
                            break;

                        case 'b': // Set traffic light color
                            printf("Enter traffic light color (g/o/r): ");
                            char trafficLightColor;
                            scanf(" %c", &trafficLightColor);

                            // Update vehicle speed based on traffic light color
                            switch (trafficLightColor) {
                                case 'g':
                                    speed = 100;
                                    break;

                                case 'o':
                                    speed = 30;
                                    break;

                                case 'r':
                                    speed = 0;
                                    break;
                            }
                            break;

                        case 'c': // Set room temperature (Temperature Sensor)
                            printf("Enter room temperature: ");
                            scanf("%d", &roomTemp);

                            // Adjust AC state based on room temperature
                            if (roomTemp < 10 || roomTemp > 30) {
                                acState = AC_ON;
                                roomTemp = 20;
                            } else {
                                acState = AC_OFF;
                            }
                            break;

                        case 'd': // Set engine temperature (Engine Temperature Sensor)
                            printf("Enter engine temperature: ");
                            scanf("%d", &engineTemp);

#if WITH_ENGINE_TEMP_CONTROLLER
                            // Adjust Engine Temperature Controller state based on engine temperature
                            if (engineTemp < 100 || engineTemp > 150) {
                                engineTempControllerState = CONTROLLER_ON;
                                engineTemp = 125;
                            } else {
                                engineTempControllerState = CONTROLLER_OFF;
                            }
#endif
                            break;
                    }
                }

                break;

            case 'b': // Turn off the vehicle engine
                printf("Turn off the vehicle engine\n\n");
                engineState = ENGINE_OFF;
                break;

            case 'c': // Quit the system
                printf("Quit the system\n");
                return 0;

            default:
                printf("Invalid input. Please try again.\n");
                break;
        }
    } while (1);

    return 0;
}

void displayMenu() {
    printf("a. Turn on the vehicle engine\n");
    printf("b. Turn off the vehicle engine\n");
    printf("c. Quit the system\n\n");
}

void displaySensorsMenu() {
    printf("\nSensors set menu:\n");
    printf("a. Turn off the engine\n");
    printf("b. Set traffic light color\n");
    printf("c. Set room temperature\n");
    printf("d. Set engine temperature\n");
}

void displayVehicleState(enum EngineState engineState, enum ACState acState, int speed, int roomTemp, int engineTemp, enum EngineTempControllerState controllerState) {
    printf("\nCurrent Vehicle State:\n");
    printf("Engine state: %s\n", engineState == ENGINE_ON ? "ON" : "OFF");
    printf("AC: %s\n", acState == AC_ON ? "ON" : "OFF");
    printf("Vehicle Speed: %d km/h\n", speed);
    printf("Room Temperature: %d\n", roomTemp);
    printf("Engine Temperature Controller State: %s\n", controllerState == CONTROLLER_ON ? "ON" : "OFF");
    printf("Engine Temperature: %d\n", engineTemp);
    printf("\n");
}
