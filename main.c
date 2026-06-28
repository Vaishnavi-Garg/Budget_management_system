#include <stdio.h>
#include <stdlib.h>

#include "modules/auth.h"
#include "modules/expenses.h"

void showMenu() {
    printf("\n===== Budget Management System =====\n");
    printf("1. Set Budget\n");
    printf("2. Add Expenses\n");
    printf("3. Update Expense\n");
    printf("4. Delete Expense\n");
    printf("5. Generate Report\n");
    printf("6. Remaining Budget\n");
    printf("7. Delete Account\n");
    printf("8. Logout\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    char currentUser[50];

    while (1) {
        printf("\n==== Welcome to BMS ====\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            if (loginUser(currentUser)) {
                printf("Login successful. Welcome, %s!\n", currentUser);

                while (1) {
                    showMenu();
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            setBudget(currentUser);
                            break;

                        case 2:
                            addExpenses(currentUser);
                            break;

                        case 3:
                            updateExpense(currentUser);
                            break;

                        case 4:
                            deleteExpense(currentUser);
                            break;

                        case 5:
                            generateReport(currentUser);
                            break;

                        case 6:
                            remainingBudget(currentUser);
                            break;

                        case 7:
                            deleteAccount(currentUser);
                            printf("Account deleted. Logging out...\n");
                            break;

                        case 8:
                            printf("Logging out...\n");
                            break;

                        default:
                            printf("Invalid choice.\n");
                    }

                    if (choice == 7 || choice == 8)
                        break;
                }
            }
            else {
                printf("Login failed. Try again.\n");
            }
        }
        else if (choice == 3) {
            printf("Exiting program...\n");
            exit(0);
        }
        else {
            printf("Invalid option.\n");
        }
    }

    return 0;
}