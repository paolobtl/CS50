 /********************************************************************
  * Assignment: https://cs50.harvard.edu/x/2022/psets/4/recover/     *
  * Goal: Implement a program that recovers JPEGs from aimage        *
  *                                                                  *
  *                                                                  *
  * @ Paolo Bietolini                                                *
  * 2022                                                             *
  ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BLOCK 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    BYTE buffer[BLOCK];
    char *filename = malloc(sizeof(char));
    int count = 0, foundimg = 0;
    FILE *img = NULL;

    //Open memory card
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Error! Could not open file called '%s'\n", argv[1]);
        return 1;
    }

    //Read from memory card until the end
    while (fread(buffer, sizeof(BLOCK), 1, file) != 0)
    {
        //Check if the file is a .jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //We found the start of a new pic so close out current picture
            if (foundimg == 1)
            {
                fclose(img);
            }
            else
            {
                foundimg = 1;
            }
            
            //Initialize a new filename and open it
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            count++;
        }

        if (foundimg == 1)
        {
            //write 512 bytes to file
            fwrite(buffer, sizeof(BLOCK), 1, img);
        }
    }
    
    free(filename);
    fclose(img);
    fclose(file);
}
