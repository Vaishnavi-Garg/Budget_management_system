#include <stdio.h>
#include <stdlib.h>
#include "string_utils.h"
#include "auth.h"
#include "expenses.h"

#define USERS_FILE "data/users.txt"

void registerUser()
{
    FILE *fp = fopen(USERS_FILE, "a+");
    if (!fp)
    {
        printf("Error opening users file.\n");
        return;
    }

    User u, temp;

    printf("Enter new username: ");
    scanf("%s", u.username);

    rewind(fp);
    while (fscanf(fp, "%s %s", temp.username, temp.password) != EOF)
    {
        if (myStrcmp(temp.username, u.username) == 0 )
        {
            printf("Username already exists.\n");
            fclose(fp);
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", u.password);

    fprintf(fp, "%s %s\n", u.username, u.password);
    fclose(fp);

    printf("User registered successfully.\n");
}

int loginUser(char currentUser[])
{
    FILE *fp = fopen(USERS_FILE, "r");
    if (!fp)
    {
        printf("No users registered.\n");
        return 0;
    }

    char username[50], password[50];
    User *u = (User *)malloc(sizeof(User));

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    while (fscanf(fp, "%s %s", u->username, u->password) != EOF)
    {
        if (myStrcmp(u->username, username) == 0 &&
            myStrcmp(u->password, password) == 0 )
        {
            myStrcpy(currentUser, username);
            fclose(fp);
            free(u);
            return 1;
        }
    }

    free(u);
    fclose(fp);
    return 0;
}

void deleteAccount(char username[])
{
    FILE *fp = fopen(USERS_FILE, "r");
    FILE *temp = fopen("data/temp_users.txt", "w");

    if (!fp || !temp)
    {
        printf("File error.\n");
        return;
    }

    User u;
    int found = 0;

    // Delete user
    while (fscanf(fp, "%s %s", u.username, u.password) != EOF)
    {
        if (myStrcmp(u.username, username) == 0)
        {
            found = 1;
            continue;
        }
        fprintf(temp, "%s %s\n", u.username, u.password);
    }

    fclose(fp);
    fclose(temp);

    remove(USERS_FILE);
    rename("data/temp_users.txt", USERS_FILE);

    // Delete user's expenses
    FILE *efp = fopen("data/expenses.txt", "r");
    FILE *etemp = fopen("data/temp_expenses.txt", "w");

    if (efp && etemp)
    {
        Expense e;

        while (fscanf(efp, "%s %s %f %s",
                      e.username, e.category, &e.amount, e.date) != EOF)
        {
            if (myStrcmp(e.username, username) == 0)
                continue;

            fprintf(etemp, "%s %s %f %s\n",
                    e.username, e.category, e.amount, e.date);
        }

        fclose(efp);
        fclose(etemp);

        remove("data/expenses.txt");
        rename("data/temp_expenses.txt", "data/expenses.txt");
    }

    // Delete user's budgets
    FILE *bfp = fopen("data/budgets.txt", "r");
    FILE *btemp = fopen("data/temp_budgets.txt", "w");

    if (bfp && btemp)
    {
        Budget b;

        while (fscanf(bfp, "%s %s %f",
                      b.username, b.category, &b.totalBudget) != EOF)
        {
            if (myStrcmp(b.username, username) == 0)
                continue;

            fprintf(btemp, "%s %s %f\n",
                    b.username, b.category, b.totalBudget);
        }

        fclose(bfp);
        fclose(btemp);

        remove("data/budgets.txt");
        rename("data/temp_budgets.txt", "data/budgets.txt");
    }

    if (found)
        printf("Account and all related data deleted successfully.\n");
    else
        printf("User not found.\n");
}