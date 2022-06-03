 /********************************************************************
  * Assignment: https://cs50.harvard.edu/x/2022/psets/2/substitution/*
  * Goal: Substitution cipher using a given key                      *
  *                                                                  *
  *                                                                  *
  * @ Paolo Bietolini                                                *
  * 2022                                                             *
  ********************************************************************/


#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool string_validation(string s);
char substitution(char c, string s);
int main(int argc, string argv[])
{
    string plaintext;

    // Command-line arguments validation
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (!string_validation(argv[1]))
    {
        printf("Usage: ./substitution key\nKey must contain 26 unique characters.\n");
        return 1;
    }

    // If the validation has been passed prompts for the plaintext
    plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    // Iterates through each char of plaintext
    for (int i = 0; i < strlen(plaintext); i++)
    {
        substitution(plaintext[i], argv[1]);
    }

    printf("\n");
    return 0;
}

// Used to validate the command-line arguments
bool string_validation(string s)
{
    if (strlen(s) < 26)
    {
        return false;
    }
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }

    for (int i = 0; i < strlen(s); i++)
    {
        for (int j = i + 1; j < strlen(s); j++)
        {
            if (s[i] == s[j])
            {
                return false;
            }
        }
    }
    return true;
}

// This functions prints the s charachter at c position
char substitution(char c, string s)
{
    if isupper(c)
    {
        printf("%c", toupper(s[c % 'A']));
    }
    else if islower(c)
    {
        printf("%c", tolower(s[c % 'a']));
    }
    else
    {
        printf("%c", c);
    }
    return 0;
}
