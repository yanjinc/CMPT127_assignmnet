/*
 * imgops.c - Simple operations on images
 *
 * C laboratory exercises.
 * Richard Vaughan, 2014.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*-------------------------------------------------
  PART 0: OPERATIONS ON A PIXEL 
*/

// get the value in the array at coordinate (x,y)
uint8_t get_pixel( const uint8_t array[], 
           unsigned int cols, 
           unsigned int rows,
           unsigned int x,
           unsigned int y )
{
    assert( x < cols );
    assert( y < rows );
    return array[ y*cols + x ];
}

// set the pixel at coordinate {x,y} to the specified color
void set_pixel( uint8_t array[], 
        unsigned int cols, 
        unsigned int rows,
        unsigned int x,
        unsigned int y,
        uint8_t color )
{
    assert( x < cols );
    assert( y < rows );
    array[ y * cols + x ] = color;
} 


/*-------------------------------------------------
  PART 1: OPERATIONS ON THE WHOLE IMAGE 
*/


/* TASK 1 - Easy functions to get started */

// Set every pixel to 0 (black) 
void zero( uint8_t array[],
	   unsigned int cols,
	   unsigned int rows )
{
    for (unsigned int i = 0; i < cols*rows; i++)
    {
        array[i] = 0;
    }
}

// Returns a pointer to a freshly allocated array that contains the
// same values as the original array, or a null pointer if the
// allocation fails. The caller is responsible for freeing the array
// later.
uint8_t* copy( const uint8_t array[], 
           unsigned int cols, 
           unsigned int rows )
{
    uint8_t* array_copy = malloc(cols*rows*sizeof(uint8_t));

    for (unsigned int i=0; i<cols*rows; i++) 
    {
        memcpy( &array_copy[i], &array[i], sizeof(array[0]) );
    }

    if (array_copy == NULL) 
    {
        printf("allocation failed\n");
        return NULL;
    } 

    return array_copy;
}

// Return the darkest color that appears in the array; i.e. the
// smallest value
uint8_t min( const uint8_t array[], 
	     unsigned int cols, 
	     unsigned int rows )
{
  uint8_t minSoFar = array[0];
  
  for (unsigned int i=0; i<cols*rows; i++)
  {
      if (array[i] < minSoFar) {
          minSoFar = array[i];
      }
  }

  return minSoFar;
}

// Return the lightest color that appears in the array; i.e. the
// largest value
uint8_t max( const uint8_t array[], 
		 unsigned int cols, 
		 unsigned int rows )
{
  uint8_t maxSoFar = array[0];
  
  for (unsigned int i=0; i<cols*rows; i++) 
  {
      if(array[i] > maxSoFar) {
          maxSoFar = array[i];
      }
  }

  return maxSoFar;
}

// TASK 2

//  Replace every instance of pre_color with post_color.
void replace_color(  uint8_t array[], 
		     unsigned int cols, 
		     unsigned int rows,
		     uint8_t pre_color,
		     uint8_t post_color )
{
    for (unsigned int py=0; py<rows; py++) 
    {
        for (unsigned int px=0; px<cols; px++) 
        {
            if (get_pixel(array, cols, rows, px, py) == pre_color) 
            {
                set_pixel(array, cols, rows, px, py, post_color);
            }
        }
    }

}

/* TASK 3  - two functions */


// flip the image, left-to-right, like in a mirror.
void flip_horizontal( uint8_t array[], 
              unsigned int cols, 
              unsigned int rows )
{
    for (unsigned int y=0; y<rows; y++)
    {
        for (unsigned int x=0; x<cols/2; x++)
        {   
            uint8_t temp1 = get_pixel(array, cols, rows, x, y);
            uint8_t temp2 = get_pixel(array, cols, rows, cols-x-1, y);
            set_pixel(array, cols, rows, x, y, temp2);
            set_pixel(array, cols, rows, cols-x-1, y, temp1);
        }
    }
}

// flip the image top-to-bottom.
void flip_vertical( uint8_t array[], 
            unsigned int cols, 
            unsigned int rows )
{
    for (unsigned int y=0;y<rows/2;y++)
    {
        for (unsigned int x=0;x<cols;x++)
        {
            uint8_t temp1 = get_pixel(array, cols, rows, x, y);
            uint8_t temp2 = get_pixel(array, cols, rows, x, rows-y-1);
            set_pixel(array, cols, rows, x, y, temp2);
            set_pixel(array, cols, rows, x, rows-y-1, temp1);
        } 
    }
}

/* TASK 4 */

// Find the first coordinate of the first pixel with a value that
// equals color. Search from left-to-right, top-to-bottom. If it is
// found, store the coordinates in *x and *y and return 1. If it is
// not found, return 0.
int locate_color(  const uint8_t array[], 
		   unsigned int cols, 
		   unsigned int rows,
		   uint8_t color,
		   unsigned int *x,
		   unsigned int *y )
{
    for (unsigned int py=0;py<rows;py++)
    {
        for (unsigned int px=0;px<cols;px++)
        {
            if ( get_pixel(array, cols,rows,px,py) == (color) )
            {

                *x = px;
                *y = py;
                return 1;
            }
        }
    }
    return 0;
}


/* TASK 5 */

// Invert the image, so that black becomes white and vice versa, and
// light shades of grey become the corresponding dark shade. 
void invert( uint8_t array[], 
         unsigned int cols, 
         unsigned int rows )
{
    for (unsigned int i=0; i<cols*rows; i++) {
        array[i] = 255 - array[i];
    }
}

/* TASK 6 */

// Multiply every pixel by scale_factor, in order to brighten or
// darken the image. Resulting values are rounded to the nearest
// integer (0.5 rounded up) and any resulting value over 255 is
// thresholded to 255.
void scale_brightness( uint8_t array[],
            unsigned int cols,
            unsigned int rows,
            double scale_factor )
{
    for (int pixel=0;pixel<(cols*rows);pixel++)
    {
        if ((array[pixel]*scale_factor)>255)
        {
            array[pixel]=255;
        }
        else
       {
          array[pixel]= round(array[pixel]*scale_factor);   
       }
    }
}


/* TASK 7 */

// Normalize the dynamic range of the image, i.e. Shift and scale the
// pixel colors so that that darkest pixel is 0 and the lightest pixel
// is 255. Hint: you already wrote min() and max(). 
void normalize( uint8_t array[],
        unsigned int cols,
        unsigned int rows )
{
  int i;
  unsigned int cc=cols;
  unsigned int rr=rows;
  
  uint8_t arr[rr*cc];
  for (i=0;i<rr*cc;i++)
  {
    arr[i]=array[i];
  }    
  int x=max(arr,cc,rr);
  int n=min(arr,cc,rr);
  for (i=0;i<rows*cols;i++)
  {
    array[i]=array[i]-n;  
  }  
  
  for (i=0;i<rows*cols;i++)
  {
    array[i]=round(array[i]*255.0/(x-n));    
  }  
}

/* TASK 8 */

// Return a new image of size rows/2 by cols/2 If the original image              
// has an odd number of columns, ignore its rightmost column. If the              
// original image has an odd number of rows, ignore its bottom row.               
// The value of a pixel at (p,q) in the new image is the average of               
// the four pixels at (2p,2q), (2p+1,2q), (2p+1,2q+1), (2p,2q+1) in               
// the original image.                                                            
uint8_t* half( const uint8_t array[],
	       unsigned int cols,
	       unsigned int rows )
{
  // your code here

  uint8_t* new_array = malloc(sizeof(uint8_t)*(rows/2)*(cols/2));
  if (new_array == NULL)
      {
        printf( "failed to allocate memory for image.\n" );
        exit(1);
      }

  for (unsigned int py=0; py<rows/2; py++) {
      for (unsigned int px=0; px<cols/2; px++) {

          uint8_t temp1 = get_pixel(array, cols,rows,2*px,2*py);
          uint8_t temp2 = get_pixel(array, cols,rows,2*px+1,2*py);
          uint8_t temp3 = get_pixel(array, cols,rows,2*px,2*py+1);
          uint8_t temp4 = get_pixel(array, cols,rows,2*px+1,2*py+1);

          uint8_t avg = round((temp1+temp2+temp3+temp4)/4.0);

          set_pixel(new_array,cols/2,rows/2,px,py,avg);
      }
  }

  return new_array;
}




/*-------------------------------------------------
  PART 2: OPERATIONS ON IMAGE SUB-REGIONS

  These functions operate only on a rectangular region of the array
  defined by a (left,top) corner (i.e. closer to the image origin) and
  (right,bottom) corner (i.e. further from the image origin).

  The rectangle edges of a rectangular region are aligned with the x,y axes. 
  
  The region includes all the columns from [left, right-1] inclusive,
  and all the rows from [top, bottom-1] inclusive.
  
  In every case, you may assume that left <= right and top <= bottom:
  do not need to test for this.

  The area of the region is right-left * bottom-top pixels, which
  implies that if left == right or top == bottom, the region has no
  area and is defined as "empty". Each function notes how to handle
  empty regions.
 
  In every function, you can use assert() to test bounds on the region
  corners.
*/

/* TASK 9 */

// Set every pixel in the region to color. If the region is empty, the
// image must remained unchanged.
void region_set( uint8_t array[], 
         unsigned int cols, 
         unsigned int rows,
         unsigned int left,
         unsigned int top,
         unsigned int right,
         unsigned int bottom,
         uint8_t color )
{
    // your code here
    // consider empty region
    if ((top!=bottom) && (left!=right)) 
    {
        for (unsigned int py=top; py<bottom; py++) 
        {
            for (unsigned int px=left; px<right; px++) 
            {
                set_pixel(array, cols, rows, px, py, color); 
            }
        }
    }

}

/* TASK 10 */

// Return the sum of all the pixels in the region. Notice the large
// return type to handle potentially large numbers. Empty regions
// return the sum 0.
unsigned long int region_integrate( const uint8_t array[], 
                    unsigned int cols, 
                    unsigned int rows,
                    unsigned int left,
                    unsigned int top,
                    unsigned int right,
                    unsigned int bottom )
{
    // your code here
    unsigned int sum=0;

    if ((top!=bottom) && (right!= left))
    {
        for (unsigned int py=top; py<bottom; py++)
        {
            for (unsigned int px=left; px<right; px++)
            {
                sum += get_pixel(array, cols, rows, px, py);
            }
        }

        return sum;
    } else {
        return sum;
    }
}

/* TASK 11 */

// Get a new image which is a copy of the region. Empty regions return
// a null pointer. If memory allocation fails, return a null
// pointer. The caller is responsible for freeing the returned array
// later.
uint8_t* region_copy( const uint8_t array[], 
              unsigned int cols, 
              unsigned int rows,
              unsigned int left,
              unsigned int top,
              unsigned int right,
              unsigned int bottom )
{
    // your code here
    if (top == bottom || left == right) {
        return NULL;
    }

    uint8_t* new_array = malloc((right-left)*(bottom-top)*sizeof(uint8_t));
    if (new_array == NULL)
    {
        printf( "failed to allocate memory for image.\n" );
        return NULL;
    }

    for (unsigned int py=top; py<bottom; py++) 
    {
        for (unsigned int px=left; px<right; px++) 
        {
            uint8_t temp = get_pixel(array, cols, rows, px, py);
            set_pixel(new_array, (right-left), (bottom-top), px-left, py-top, temp);
        }
    }


    return new_array;
}


