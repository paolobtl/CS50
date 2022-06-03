 /********************************************************************
  * Assignment: https://cs50.harvard.edu/x/2022/psets/1/mario/more/  *
  * Goal: Print a pyramid                                            *
  *                                                                  *
  * @ Paolo Bietolini                                                *
  * 2022                                                             *
  ********************************************************************/


#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    //Prompt the user
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //Prints rows
    for (int i = 0; i < height; i++)
    {
        //Prints spaces
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        //Prints hashes
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
