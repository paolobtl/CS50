#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    string plaintext;
    int key;

    //Input validation
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Convert the input key to a int
    key = atoi(argv[1]);
    plaintext = get_string("plaintext: ");
    printf("ciphertext: ");


    //Loop over the plaintext and rotate the letters using the rotate() function
    for (int i = 0; i < strlen(plaintext); i++)
    {
        rotate(plaintext[i], key);
    }

    printf("\n");
    return 0;
}

//Checks if the input is a digit
bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        char ch = s[i];
        if (!isdigit(ch))
        {
            return false;
        }
    }
    return true;
}

//Rotates the plaintext according to a key, if it's a symbol or non-printable char this won't be rotated
char rotate(char c, int n)
{
    if (isalpha(c))
    {
        //The x variable determines uses the ASCII value of the letter 'A' or 'a'
        int x = (isupper(c)) ? 65 : 97;
        c = ((int)c + n - x) % 26 + x;
        printf("%c", c);
    }
    else
    {
        printf("%c", c);
    }
    return 0;
}
