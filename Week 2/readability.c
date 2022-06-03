 /********************************************************************
  * Assignment: https://cs50.harvard.edu/x/2022/psets/2/readability/ *
  * Goal: Returns the reading grade level                            *
  *       according to the Coleman-Liau index                        *
  *                                                                  *
  * @ Paolo Bietolini                                                *
  * 2022                                                             *
  ********************************************************************/

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int main(void) 
{
    string s = get_string("Text: ");
    int lett, sent, words;
    lett = sent = words = 0;

    //String iteration
    for (int i = 0; i < strlen(s); i++)

        //Letters, words and sentences counting
    {
        if (isalpha(s[i]))
        {
            lett++;
        }

        //This condition checks if there are spaces or we are at the beginning/end of the sentence
        if (isspace(s[i]) || (s[i] != ' ' && i == 0))
        {
            words++;
        }


        if (s[i] == '?' || s[i] == '!' || s[i] == '.')
        {
            sent++;
        }
    }

    //Coleman–Liau index
    float L = (lett / (float) words) * 100;
    float S = (sent / (float) words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    //Grade printing
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
