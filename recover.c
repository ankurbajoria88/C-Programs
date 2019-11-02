/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include<cs50.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

typedef uint8_t BYTE;

struct Buffer {
    BYTE data[512];
};

struct Buffer buf;

int main(int argc, char* argv[])
{
    
    // Open file card.raw
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL) {
        printf("Could not open card.raw");
        return 2;
    }
    
    int filename = 0;
    bool writeToFile = false;
    FILE* img;
    fread(buf.data, 512, 1, inptr);
    
    while (fread(buf.data, 512, 1, inptr) > 0) {

        // Check to see if a jpeg header is found
        // If jpeg image found then open a new file and write to it until next header
        BYTE jpegHeader1[4] = {0xff, 0xd8, 0xff, 0xe0};
        BYTE jpegHeader2[4] = {0xff, 0xd8, 0xff, 0xe1};
    
        int checkCounter = 0;
        for (int i = 0; i < 4; i++) {
            if (buf.data[i] == jpegHeader1[i] || buf.data[i] == jpegHeader2[i]) {
            checkCounter ++;
            }
        }
    
        // If it is a jpeg header then start writing it to a file 
        if (checkCounter == 4) {
            char file[8];
            sprintf(file, "%03i.jpg", filename);
            
            // If a file doesn't already exist, create one and write the data
            if (!writeToFile) {
                img = fopen(file, "w");
                fwrite(buf.data, 512, 1, img);
                writeToFile = true;
                filename ++;
            }else {
                // If there was a file being used, close it and open a new one
                fclose(img);
                img = fopen(file, "w");
                fwrite(buf.data, 512, 1, img);
                filename ++;
            }
        }else {
            // Keep writing data
            if (writeToFile) {
                fwrite(buf.data, 512, 1, img);
            }
        }
    }
    
    // Close jpeg file
    if (img) {
        fclose(img);
    }
    
    // Close card.raw
    fclose(inptr);
    
    return 0;
}
