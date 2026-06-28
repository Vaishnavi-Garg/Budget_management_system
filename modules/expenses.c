#include "expenses.h"
#include <stdio.h>
#include <stdlib.h>
#include "string_utils.h"

#define EXPENSE_FILE "data/expenses.txt"
#define BUDGET_FILE "data/budgets.txt"

void setBudget(char user[])
{
    FILE *fp = fopen(BUDGET_FILE, "r");
    FILE *temp = fopen("data/temp.txt", "w");

    if (!fp || !temp)
    {
        printf("File error.\n");
        return;
    }

    Budget b;
    char category[50];
    float newBudget;
    int found = 0;

    printf("Enter Category: ");
    scanf(" %[^\n]", category);
    trim(category);
    strlwr_custom(category);

    printf("Enter total budget: ");
    scanf("%f", &newBudget);

    while (fscanf(fp, "%s %s %f",
                  b.username, b.category, &b.totalBudget) != EOF)
    {
        if (myStrcmp(b.username, user) == 0 &&
            myStrcmp(b.category, category) == 0)
        {
            // Update existing budget
            b.totalBudget = newBudget;
            found = 1;
        }

        fprintf(temp, "%s %s %f\n",
                b.username, b.category, b.totalBudget);
    }

    if (!found)
    {
        fprintf(temp, "%s %s %f\n",
                user, category, newBudget);
    }

    fclose(fp);
    fclose(temp);

    remove(BUDGET_FILE);
    rename("data/temp.txt", BUDGET_FILE);

    if (found)
        printf("Budget updated successfully.\n");
    else
        printf("Budget added successfully.\n");
}

void addExpenses(char user[])
{
    FILE *fp = fopen(EXPENSE_FILE, "a");

    if (!fp)
    {
        printf("Error opening file.\n");
        return;
    }

    Expense e;
    myStrcpy(e.username, user);

    printf("Enter category: ");
    scanf(" %[^\n]", e.category);
    trim(e.category);
    strlwr_custom(e.category);

    printf("Enter amount: ");
    scanf("%f", &e.amount);

    printf("Enter date ( DD/MM/YYYY): ");
    scanf(" %[^\n]", e.date);
    trim(e.date);

    fprintf(fp, "%s %s %f %s\n",
            e.username, e.category, e.amount, e.date);

    fclose(fp);

    printf("Expense added.\n");

    //  BUDGET ALERT

    float spent = 0, limit = 0;
    Expense temp;
    Budget b;

    // Calculate total spent in this category
    fp = fopen(EXPENSE_FILE, "r");
    if (fp)
    {
        while (fscanf(fp, "%s %s %f %s",
                      temp.username, temp.category,
                      &temp.amount, temp.date) != EOF)
        {
            if (myStrcmp(temp.username, user) == 0 &&
                myStrcmp(temp.category, e.category) == 0 )
            {
                spent += temp.amount;
            }
        }
        fclose(fp);
    }

    // Get budget limit
    FILE *bfp = fopen(BUDGET_FILE, "r");
    if (bfp)
    {
        while (fscanf(bfp, "%s %s %f",
                      b.username, b.category,
                      &b.totalBudget) != EOF)
        {
            if (myStrcmp(b.username, user) == 0 &&
                myStrcmp(b.category, e.category) == 0 )
            {
                limit = b.totalBudget;
                break;
            }
        }
        fclose(bfp);
    }

    if (limit == 0)
    {
        printf("Budget for this category is not set!\n");
    }
    else if (spent > limit)
    {
        printf("ALERT: Budget exceeded for category '%s'!\n", e.category);
    }
}

void updateExpense(char user[])
{
    FILE *fp = fopen(EXPENSE_FILE, "r");
    FILE *temp = fopen("data/temp.txt", "w");

    if (!fp || !temp)
    {
        printf("File error.\n");
        return;
    }

    Expense e;
    char category[50], date[20];
    float amount;
    int found = 0;

    // Ask which expense to update
    printf("Enter category: ");
    scanf(" %[^\n]", category);
    trim(category);
    strlwr_custom(category);

    printf("Enter previous amount of expense: ");
    scanf("%f", &amount);

    printf("Enter previous date of expense (DD/MM/YYYY): ");
    scanf(" %[^\n]", date);
    trim(date);

    while (fscanf(fp, "%s %s %f %s",
                  e.username, e.category, &e.amount, e.date) != EOF)
    {
        if (myStrcmp(e.username, user) == 0 &&
            myStrcmp(e.category, category) == 0 &&
            e.amount == amount &&
            myStrcmp(e.date, date) == 0 &&
            found == 0)
        {
            printf("Enter new amount: ");
            scanf("%f", &e.amount);

            printf("Enter new date (DD/MM/YYYY): ");
            scanf(" %[^\n]", e.date);
            trim(e.date);

            found = 1;
        }

        fprintf(temp, "%s %s %f %s\n",
                e.username, e.category, e.amount, e.date);
    }

    fclose(fp);
    fclose(temp);

    remove(EXPENSE_FILE);
    rename("data/temp.txt", EXPENSE_FILE);

    if (found)
        printf("Expense updated successfully.\n");
    else
        printf("No matching expense found.\n");
}

void deleteExpense(char user[])
{
    FILE *fp = fopen(EXPENSE_FILE, "r");
    FILE *temp = fopen("data/temp.txt", "w");

    if (!fp || !temp)
    {
        printf("File error.\n");
        return;
    }

    Expense e;
    char search[50];
    int found = 0;

    printf("Enter category to delete all expenses: ");
    scanf(" %[^\n]", search);
    trim(search);
    strlwr_custom(search);

    while (fscanf(fp, "%s %s %f %s",
                  e.username, e.category, &e.amount, e.date) != EOF)
    {
        if (myStrcmp(e.username, user) == 0 &&
            myStrcmp(e.category, search) == 0)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%s %s %f %s\n",
                e.username, e.category, e.amount, e.date);
    }

    fclose(fp);
    fclose(temp);

    remove(EXPENSE_FILE);
    rename("data/temp.txt", EXPENSE_FILE);

    if (found)
        printf("All matching expenses deleted.\n");
    else
        printf("No matching expense found.\n");
}

void generateReport(char user[])
{
    FILE *fp = fopen(EXPENSE_FILE, "r");

    if (!fp)
    {
        printf("File error.\n");
        return;
    }

    Expense *e = (Expense *)malloc(sizeof(Expense));

    printf("\n===== REPORT =====\n");

    while (fscanf(fp, "%s %s %f %s",
                  e->username, e->category, &e->amount, e->date) != EOF)
    {
        if (myStrcmp(e->username, user) == 0 )
        {
            printf("%s | %s | %.2f\n", e->date, e->category, e->amount);
        }
    }

    free(e);
    fclose(fp);
}

void remainingBudget(char user[])
{
    FILE *efp = fopen(EXPENSE_FILE, "r");
    FILE *bfp = fopen(BUDGET_FILE, "r");

    if (!efp || !bfp)
    {
        printf("No data available.\n");
        return;
    }

    Budget b;
    Expense e;

    printf("\n========== Category-wise Budget Status ==========\n");

     while (fscanf(bfp, "%s %s %f",
                  b.username, b.category, &b.totalBudget) != EOF)
    {
        if (myStrcmp(b.username, user) == 0)
        {
            float spent = 0;

            rewind(efp);

            while (fscanf(efp, "%s %s %f %s",
                          e.username, e.category, &e.amount, e.date) != EOF)
            {
                if (myStrcmp(e.category, b.category) == 0 &&
                    myStrcmp(e.username, user) == 0)
                {
                    spent += e.amount;
                }
            }

            printf("\nCategory: %s\n", b.category);
            printf("Budget: %.2f\n", b.totalBudget);
            printf("Spent: %.2f\n", spent);
            printf("Remaining: %.2f\n", b.totalBudget - spent);
        }
    }

    fclose(efp);
    fclose(bfp);
}
