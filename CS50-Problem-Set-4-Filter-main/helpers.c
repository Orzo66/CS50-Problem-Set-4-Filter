#include "helpers.h"
#include <math.h>

#define RED 0
#define GREEN 1
#define BLUE 2
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int gray = round((image[row][column].rgbtBlue + image[row][column].rgbtGreen + image[row][column].rgbtRed) / 3.0);
            image[row][column].rgbtBlue = image[row][column].rgbtGreen = image[row][column].rgbtRed = gray;
        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int sepiaRed = round(.393 * image[row][column].rgbtRed + .769 * image[row][column].rgbtGreen + .189 * image[row][column].rgbtBlue);
            int sepiaGreen = round(.349 * image[row][column].rgbtRed + .686 * image[row][column].rgbtGreen + .168 * image[row][column].rgbtBlue);
            int sepiaBlue = round(.272 * image[row][column].rgbtRed + .534 * image[row][column].rgbtGreen + .131 * image[row][column].rgbtBlue);

            image[row][column].rgbtRed = fmin(255, sepiaRed);
            image[row][column].rgbtBlue = fmin(255, sepiaBlue);
            image[row][column].rgbtGreen = fmin(255, sepiaGreen);
        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width / 2; column++)
        {
            original = image[row][column];
            image[row][column] = image[row][width - column - 1];
            image[row][width - column - 1] = original;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            copy[row][column] = image[row][column];
        }

    }

    float red, green, blue;
    red = green = blue = 0;
    int count = 0;

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            for (int arrow = row - 1; arrow <= row + 1; arrow++)
            {
                for (int arrcol = column - 1; arrcol <= column + 1; arrcol++)
                {
                    if (arrcol < width && arrow < height && arrcol >= 0 && arrow >= 0)
                    {
                        red += copy[arrow][arrcol].rgbtRed;
                        green += copy[arrow][arrcol].rgbtGreen;
                        blue += copy[arrow][arrcol].rgbtBlue;
                        count++;
                    }
                }
            }
            image[row][column].rgbtRed = round(red / count);
            image[row][column].rgbtGreen = round(green / count);
            image[row][column].rgbtBlue = round(blue / count);
            count = 0;
            red = green = blue = 0;
        }
    }
    return;
}
