 /********************************************************************
  * Assignment: https://cs50.harvard.edu/x/2022/psets/4/filter/less/ *
  * Goal: Implement image filtering algorithms                       *
  *                                                                  *
  *                                                                  *
  * @ Paolo Bietolini                                                *
  * 2022                                                             *
  ********************************************************************/

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Sum and round the original values into a new variable
            float rgbtGrayscale = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.000);

            //Copy new variable's values into originals
            image[i][j].rgbtBlue = rgbtGrayscale;
            image[i][j].rgbtGreen = rgbtGrayscale;
            image[i][j].rgbtRed = rgbtGrayscale;
        }
    }
    return;
}
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // If the sepia value is > 255 then it should be apped to 255
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        //Iterate for half of the width to avoid move pixels
        //into original positions
        for (int j = 0; j < width / 2; j++)
        {
            //Use a temp variable to store original values
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyImage[height][width];

    // Create a copy of the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyImage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Colour variables to contain the total amounf of colour for each pixel
            int red, blue, green;
            red = blue = green = 0;

            // C is the number of the scanned pixels in the kernel

            float c = 0.00;

            // Get the neighbouring pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1 ; y < 2; y++)
                {
                    // Current pixel
                    int cX = x + i;
                    int cY = y + j;

                    // Check if the kernel is outside the boundaries
                    if (cX < 0 || cX > (height - 1) || cY < 0 || cY > (width - 1))
                    {
                        continue;
                    }

                    // Get the colour value
                    red += copyImage[cX][cY].rgbtRed;
                    green += copyImage[cX][cY].rgbtGreen;
                    blue += copyImage[cX][cY].rgbtBlue;
                    c++;
                }

                // Calculate the average colour for the neighbouring pixels
                image[i][j].rgbtRed = round(red / c);
                image[i][j].rgbtBlue = round(blue / c);
                image[i][j].rgbtGreen = round(green / c);
            }
        }
    }
    return;
}
