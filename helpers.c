#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

char* concat(char* first, char* second)
{
    // Concatenates two strings such that first is followed by second

    // Allocate memory for the first concatenation
        char *cat = malloc(sizeof(char) * (strlen(first) + strlen(second) + 1));

        // Make sure memory was successfully allocated
        if (cat == NULL)
        {   
            print("Error 6: Could not allocate memory");
            return "";
        }

        // Copy the first string to the allocated memory
        for (int i = 0; i < (strlen(first) + 1); i++)
        {
            cat[i] = first[i];
        }

        // Concatenate first string with second string
        strcat(cat, second);

        return cat;
}

int get_digits(int num)
{
    // Gets the amount of digits a number has

    int digits = 0;

    for (int i = 0; tenToThe(i) <= num; i++)
    {
        digits += 1;
    }
    return digits;
}

char* itoa(int num)
{
    int digits = get_digits(num);

    char* target = malloc(sizeof(char) * (digits + 1));

    for (int i = 0; num != 0; i++)
    {
        
        int digit = num % tenToThe(i + 1);
        num -= digit;
        digit = digit / tenToThe(i);
        printf("%i, %i\n", digits -1 -i, digit);
        target[digits -1 - i] = todigit(digit);
    }

    target[digits] = '\0';
    return target;
}

void print(char text[])
{
    printf("%s\n", text);
}

int tenToThe(int n)
{
    int res = 1;

    while (n != 0)
    {
        res *= 10;
        n -= 1;
    }

    return res;
}

char todigit(int digit)
{   
    // Make sure digit is a number from 0 to 9 
    digit = (digit >= 0) ? digit : (digit * (-1));
    digit = (digit < 10) ? digit : (digit % 10);

    char res = digit + 48;
    return res;
}