// image2.cpp
#include<stdlib.h>
#include<fstream>
#include "image2.hpp"
using namespace std;

/*
ERROR CODES:
-1 : Malloc function not working properly.
-2 : Out Of Scope Pixel.
-3 : File that you are trying to open cannot be opened due to some reason.
*/

/* Constructs an image of 0x0 pixels. */
Image::Image() {
    cols=0;
    rows=0;
    pixels=NULL;
}

/* Frees all memory allocated for img */
Image::~Image() {
    cols=0;
    rows=0;
    delete pixels;
}

/* Changes the size of an image, allocating memory as necessary, and setting
all pixels to fillcolor. Returns 0 on success, or a non-zero error code.*/
int Image::resize(unsigned int width, unsigned int height, uint8_t fillcolor) {
    /*Width of the image is  stored in columns.
    Height of the image is stored in rows.*/
    cols=width;
    rows=height;
    pixels=(uint8_t*)malloc(sizeof(uint8_t)*cols*rows);
    if(pixels==NULL) {
        return -1;
    }
    for(int i=0; i<rows*cols; i++) {
        pixels[i]=fillcolor;
    }
    return 0;
}

/* Sets the color of the pixel at (x,y) to color. Returns 0 on success, else a non-zero error code.
If (x,y) is not a valid pixel, the call fails and the image does not change.*/
int Image::set_pixel(unsigned int x, unsigned int y,uint8_t color) {
    if(x>=cols || y>=rows) {
        return -2;
    } else {
        pixels[(x*cols)+(y)]=color;
        return 1;
    }
}

/* Gets the color of the pixel at (x,y) and stores at the address pointed to by colorp.
Returns 0 on success, else a non-zero error code. */
int Image::get_pixel(unsigned int x, unsigned int y, uint8_t* colorp) {
    if(x>=cols || y>=rows) {
        return -2;
    } else {
        *colorp=pixels[(x*cols)+(y)];
        return 1;
    }
}

/* Saves the image in the file filename. In a format that can be loaded by load().
Returns 0 on success, else a non-zero error code. */
int Image::save(const char* filename) {
    ofstream OutputFile(filename);
    if(OutputFile.is_open()) {
        //Rows and Cols are stored first in two consecutively lines.
        OutputFile<<cols<<"\n"<<rows<<"\n";
        for(int i=0; i<rows*cols; i++) {
            if(i==rows*cols-1) {
                OutputFile<<unsigned(pixels[i]);//Does not insert a new line after the last element is inserted.
            } else {
                OutputFile<<unsigned(pixels[i])<<"\n";//Pixels is stored as one number per line.
            }
        }
        OutputFile.close();
        return 0;
    } else {
        return -3;
    }
}

/* Load the an image from the file filename, replacing the current image size and data.
The file is in a format that was saved by save().
Returns 0 success, else a non-zero error code . */
int Image::load(const char* filename) {
    ifstream InputFile(filename);
    if(InputFile.is_open()) {
        unsigned int input;
        rows=cols=0;
        bool PixelsDeclaration=false, ColsAssignment=false, RowsAssignment=false;
        int i=0;
        while(!InputFile.eof()) {
            InputFile>>input;
            if(!ColsAssignment) {
                cols=input;
                ColsAssignment = true;
            } else if(!RowsAssignment) {
                rows=input;
                RowsAssignment = true;
            } else {
                if(!PixelsDeclaration) {
                    pixels = (uint8_t*)malloc(sizeof(uint8_t)*rows*cols);
                    if(pixels == NULL) {
                        return -1;
                    }
                    pixels[i++]=input;
                    PixelsDeclaration=true;
                } else {
                    pixels[i++]=input;
                }
            }
        }
        InputFile.close();
        return 0;
    } else {
        return -3;
    }
}