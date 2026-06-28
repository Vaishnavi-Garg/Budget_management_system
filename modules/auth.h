#ifndef AUTH_H
#define AUTH_H

typedef struct {
    char username[50];
    char password[50];
} User;

void registerUser();

int loginUser(char currentUser[]);

void deleteAccount(char username[]);

#endif