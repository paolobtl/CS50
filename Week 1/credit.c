 /********************************************************************
  * Assignment: https://cs50.harvard.edu/x/2022/psets/1/credit/      *
  * Goal: Validate a credit card number                              *
  *                                                                  *
  * @ Paolo Bietolini                                                *
  * 2022                                                             *
  ********************************************************************/

#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

int length(long n);
bool is_valid_cc(long n);
int getFirst2Digits(long n);
int getFirstDigit(long n);

int main(void)
{
    long ccnum = 0;

    //Prompts the user for a credit card number
    do 
    {
        ccnum = get_long("Number: ");
    }
    while (ccnum == 0);

    int first2Digits = getFirst2Digits(ccnum);
    int firstDigit = getFirstDigit(ccnum);
    long ccCopy = ccnum;
    int l = length(ccCopy);

    //If the card is valid checks the lenght and the first two digits and prints the card brand
    if (is_valid_cc(ccnum))
    {
        if ((l == 16 || l == 13) && firstDigit == 4)
        {
            printf("VISA\n");
        }
        else if (l == 15 && (first2Digits == 34 || first2Digits == 37))
        {
            printf("AMEX\n");
        }
        else if (l == 16 && (first2Digits > 50 && first2Digits < 56))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

//Calculates the lenght of the input number
int length(long n)
{
    int len = 0;
    while (n > 0)
    {
        len++;
        n = n / 10;
    }
    return len;
}

//This boolean functions checks if a credit card number is valid, following the Luhn’s Algorithm
bool is_valid_cc(long n)
{
    int len = length(n);
    int everyOtherDigit = 0;
    int sum = 0;
    int i = 0;

    //The input number will be divided by 10 at each iteration so we can use the last digit
    //i is a counter that returns the position
    while (n > 0)
    {
        //If the digit is in a odd position then multiply it by 2
        if (i % 2 != 0)
        {
            everyOtherDigit = 2 * (n % 10);

            //If the multiplied digit is > 9 then the two digits are summed together
            if (everyOtherDigit > 9)
            {
                sum += (everyOtherDigit % 10 + everyOtherDigit / 10);
            }
            else                
            {
                sum += everyOtherDigit;
            }
        }
        //If the position is even then just add the last digit to the final sum
        else
        {
            sum += n % 10;
        }
        n = n / 10;
        i++;
    }
    //If the modulo of summed digits is 0 the the card is valid
    if (sum % 10 == 0)
    {
        return true;
    } 
    else
    {
        return false;
    }
}

//These functions return the first digit(s) of a number
int getFirst2Digits(long n)
{
    long local = n;
    while (local >= 100) 
    {
        local /= 10;
    }
    return local;
}

int getFirstDigit(long n)
{
    long local = n;
    while (local >= 10) 
    {
        local /= 10;
    }
    return local;
}
