#include "string_utils.h"

void myStrcpy(char dest[], const char src[])
{
    int i = 0;

    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';   
}

int myStrcmp(const char s1[], const char s2[])
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }

    return s1[i] - s2[i];
}

void myStrcat(char dest[], const char src[])
{
    int i = 0, j = 0;

    while (dest[i] != '\0')
        i++;

    while (src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';
}

void strlwr_custom(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    }
}

void trim(char *str)
{
    int i = 0, j = 0;
    char temp[100];
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
            temp[j++] = str[i];
        i++;
    }
    temp[j] = '\0';
    myStrcpy(str, temp);
}