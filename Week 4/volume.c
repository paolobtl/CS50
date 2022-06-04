 /********************************************************************
  * Assignment: https://cs50.harvard.edu/x/2022/labs/4/              *
  * Goal: Write a program to modify the volume of an audio file      *
  *                                                                  *
  *                                                                  *
  * @ Paolo Bietolini                                                *
  * 2022                                                             *
  ********************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    uint8_t header[HEADER_SIZE];
    int16_t buffer;


    fread(header, sizeof(header), 1, input);
    fwrite(header, sizeof(header), 1, output);

    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(buffer), 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);
    return 0;
}
