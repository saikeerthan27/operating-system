#include <stdio.h>
#include <stdbool.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
bool finish[NUMBER_OF_CUSTOMERS];

void init() {
    // Initialize available resources
    printf("Enter the available resources:\n");
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        scanf("%d", &available[i]);
    }

    // Initialize maximum resources for each customer
    printf("Enter the maximum resources for each customer:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        printf("Customer %d: ", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; ++j) {
            scanf("%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
        finish[i] = false;
    }

    // Initialize allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        printf("Customer %d: ", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; ++j) {
            scanf("%d", &allocation[i][j]);
            need[i][j] -= allocation[i][j];
            available[j] -= allocation[i][j];
        }
    }
}

bool is_safe() {
    int work[NUMBER_OF_RESOURCES];
    bool finish_copy[NUMBER_OF_CUSTOMERS];
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        work[i] = available[i];
    }
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
        finish_copy[i] = finish[i];
    }

    int count = 0;
    while (count < NUMBER_OF_CUSTOMERS) {
        bool found = false;
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; ++i) {
            if (!finish_copy[i]) {
                int j;
                for (j = 0; j < NUMBER_OF_RESOURCES; ++j) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == NUMBER_OF_RESOURCES) {
                    for (int k = 0; k < NUMBER_OF_RESOURCES; ++k) {
                        work[k] += allocation[i][k];
                    }
                    finish_copy[i] = true;
                    found = true;
                    ++count;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

bool request_resources(int customer_num, int request[]) {
    // Check if request is within need
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        if (request[i] > need[customer_num][i]) {
            printf("Request exceeds maximum claim.\n");
            return false;
        }
    }

    // Check if request is within available
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        if (request[i] > available[i]) {
            printf("Request exceeds available resources.\n");
            return false;
        }
    }

    // Simulate allocation
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        available[i] -= request[i];
        allocation[customer_num][i] += request[i];
        need[customer_num][i] -= request[i];
    }

    // Check if system is in safe state
    if (!is_safe()) {
        // Revert allocation
        for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
            available[i] += request[i];
            allocation[customer_num][i] -= request[i];
            need[customer_num][i] += request[i];
        }
        printf("Request denied. System would be in an unsafe state.\n");
        return false;
    }

    printf("Request granted.\n");
    return true;
}

void release_resources(int customer_num, int release[]) {
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        available[i] += release[i];
        allocation[customer_num][i] -= release[i];
        need[customer_num][i] += release[i];
    }
}

int main() {
    init();

    int request[NUMBER_OF_RESOURCES];
    int release[NUMBER_OF_RESOURCES];

    printf("\nAvailable resources: ");
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Enter the customer number and resources requested (or released):\n");
    int customer_num;
    char action;
    while (scanf("%d %c", &customer_num, &action) == 2) {
        for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
            scanf("%d", &request[i]);
        }
        if (action == 'R') {
            release_resources(customer_num, request);
        } else if (action == 'Q') {
            if (!request_resources(customer_num, request)) {
                printf("Request denied. Customer %d will wait.\n", customer_num);
            }
        } else {
            printf("Invalid action. Please use 'R' for release or 'Q' for request.\n");
        }

        printf("\nAvailable resources: ");
        for (int i = 0; i < NUMBER_OF_RESOURCES; ++i) {
            printf("%d ", available[i]);
        }
        printf("\n");
    }

    return 0;
}

