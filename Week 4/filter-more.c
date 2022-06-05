 /********************************************************************
  * Assignment: https://cs50.harvard.edu/x/2022/psets/4/filter/more/ *
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
            float grayScale = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.000);
            image[i][j].rgbtBlue = grayScale;
            image[i][j].rgbtGreen = grayScale;
            image[i][j].rgbtRed = grayScale;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE t = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = t;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Define the convolution kernels
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE copyImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxRed, GxGreen, GxBlue;
            GxRed = GxGreen = GxBlue = 0;

            int GyRed, GyGreen, GyBlue;
            GyRed = GyGreen = GyBlue = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1 ; y < 2; y++)
                {
                    // Current pixel
                    int cX = x + i;
                    int cY = y + j;

                    // Current kernel index
                    int cGx = x + 1;
                    int cGy = y + 1;

                    // Check if the kernel is outside the boundaries
                    if (cX < 0 || cX > (height - 1) || cY < 0 || cY > (width - 1))
                    {
                        continue;
                    }

                    // Calculating the value for each pixel
                    GxRed   += image[cX][cY].rgbtRed * Gx[cGx][cGy];
                    GxGreen += image[cX][cY].rgbtGreen * Gx[cGx][cGy];
                    GxBlue  += image[cX][cY].rgbtBlue * Gx[cGx][cGy];

                    GyRed   += image[cX][cY].rgbtRed * Gy[cGx][cGy];
                    GyGreen += image[cX][cY].rgbtGreen * Gy[cGx][cGy];
                    GyBlue  += image[cX][cY].rgbtBlue * Gy[cGx][cGy];
                }
            }

            // Colours final values
            int red = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            int green = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            int blue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));

            copyImage[i][j].rgbtRed = red > 255 ? 255 : red;
            copyImage[i][j].rgbtGreen = green > 255 ? 255 : green;
            copyImage[i][j].rgbtBlue = blue > 255 ? 255 : blue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copyImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = copyImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copyImage[i][j].rgbtBlue;
        }
    }
    return;
}

