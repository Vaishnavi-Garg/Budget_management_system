#ifndef EXPENSE_H
#define EXPENSE_H

typedef struct {
    char username[50];
    char category[50];
    float totalBudget;
} Budget;

typedef struct {
    char username[50];
    char category[50];
    float amount;
    char date[20];
} Expense;

void setBudget(char user[]);
void addExpenses(char user[]);
void updateExpense(char user[]);
void deleteExpense(char user[]);
void generateReport(char user[]);
void remainingBudget(char user[]);

#endif