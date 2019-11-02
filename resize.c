/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a file based on a factor of n.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // Take the resize factor n as input
    int n = (int) atof(argv[1]);
    
    if (n < 1 || n > 100) {
        printf("Invalid value for scaling factor n entered. Please try again with a number between 1 and 100.");
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_res;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_res = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_res;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_res = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // Change the header attributes for BITMAPINFOHEADER
    bi_res.biWidth = abs(bi_res.biWidth * n);
    bi_res.biHeight = abs(bi_res.biHeight * n);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (bi_res.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Change the header attributes for file size
    bi_res.biSizeImage = (int) (bi_res.biWidth * sizeof(RGBTRIPLE) + newPadding) * abs(bi_res.biHeight);
    bf_res.bfSize = (int) bf.bfSize - bi.biSizeImage + bi_res.biSizeImage;
    
     // write outfile's BITMAPFILEHEADER
    fwrite(&bf_res, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_res, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Vertical resize
        for (int j = 0; j < n; j++) 
        {

            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int a = 0; a < n; a++) {
                    // Horizontal resize
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // Add padding
            for (int b = 0; b < newPadding; b++)
            {
                fputc(0x00, outptr);
            }

            // Return to the start of scanline
            if (j < n -1) {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
            
        // Skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
