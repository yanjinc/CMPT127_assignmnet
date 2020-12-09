/* 
 * intarr.c
 *
 * lab 6 - task 1
 *
 * Provides a bounds-checked, resizable array of integers with
 * random-access and stack interfaces, and several utility functions
 * that operate on them.
 * 
 */

#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>
#include <string.h>

#include "intarr.h"

/* LAB 6 TASK 1 */

/*
  Save the entire array ia into a file called 'filename' in a binary
  file format that can be loaded by intarr_load_binary(). Returns
  zero on success, or a non-zero error code on failure. Arrays of
  length 0 should produce an output file containing an empty array.

  Make sure you validate the parameters before you use them.
*/
int intarr_save_binary( intarr_t* ia, const char* filename ) 
{
    if (ia==NULL) {
        return 1;
    }
    
    if (filename==NULL){
        return 2;
    }

    int returnValue = 0;
    unsigned int len = ia->len;
    FILE *f;
 
    if( NULL == (f = fopen (filename, "wb")) )
    {
        perror( "fopen failed" );
        returnValue = 3;
    }
 
    else if ( fwrite ( &len, sizeof(int), 1, f) == 1 )
    { // then write of length successful
 
        if (fwrite (ia->data, sizeof(int), len, f) == len)
        {
            returnValue = 0; // indicate success
        }
 
        else
        { // else, write of data failed
            returnValue = 4;
        }
    }
    else
    { // else, failed to write len value to file
        returnValue = 5;
    }
 
    fclose( f ); // cleanup (writes last buffer to file)
    return( returnValue );
}

/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save_binary(). Returns a pointer to a
  newly-allocated intarr_t on success, or NULL on failure.

  Make sure you validate the parameter before you use it.
*/
intarr_t* intarr_load_binary( const char* filename )
{
    if (filename == NULL)
    {
        return NULL;
    }

    unsigned int len = 0;
    FILE *f = NULL;
    intarr_t* newia = NULL;
 
    if( NULL == (f = fopen (filename, "rb")) )
    { // then, fopen failed ot file not exist
        perror( "fopen failed" );
        return NULL;
    } // end if
 
    // implied else, fopen successful
 
    if( NULL == (newia = malloc (sizeof(intarr_t)))){
        perror( "malloc failed" );
        fclose(f);
        return NULL;
    } // end if
 
    // implied else, malloc successful
 
    if( (fread (&len, sizeof(int), 1, f) != 1 ) )
    { // then fread failed
        perror( "fread failed" );
        fclose(f);
        free( newia );
        return NULL;
    } // end if
 
    // implied else, fread for len successful
 
    newia->len = len;
 
    if( NULL == (newia->data = malloc (len*sizeof(int)) ) )
    { // then malloc failed
        perror( "malloc failed" );
        fclose(f);
        free( newia );
        return NULL;
    } // end if
 
    // implied else, malloc successful
 
    if( fread( newia->data, sizeof(int), len, f ) != len )
    { // then, fread failed
        perror( "fread failed" );
        fclose(f);
        free(newia->data);
        free(newia);
        return NULL;
    } // end if
 
 
    // implied else, fread successful
 
    fclose (f);
    return newia;
  
}
