/* 
 * intarr.c
 *
 * lab 6 - task 2
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

/* LAB 6 TASK 2 */

/*
  Save the entire array ia into a file called 'filename' in a JSON
  text file array file format that can be loaded by
  intarr_load_json(). Returns zero on success, or a non-zero error
  code on failure. Arrays of length 0 should produce an output file
  containing an empty array.

  Make sure you validate the parameters before you use them.
  
  The JSON output should be human-readable.

  Examples:

  The following line is a valid JSON array:
  [ 100, 200, 300 ]
  
  The following lines are a valid JSON array:
  [ 
   100, 
   200, 
   300 
  ]
*/
int intarr_save_json( intarr_t* ia, const char* filename )
{
  if(ia == NULL)
  {
    return 1;
  }
 
  int *arr=ia->data;
  int n=ia->len;
  int i;
  FILE *p;
  
  p=fopen(filename,"w");
  if(p!=NULL)
  {
    fprintf(p,"[\n");
    for(i=0;i<n;i++) {
      if(i!=n-1)  
      {
        fprintf(p," %d,\n",arr[i]);
      }
      else
      {
        fprintf(p," %d\n",arr[i]);
      }
    }
    fprintf(p,"]");
    fclose(p);
    return 0;
  }
  return 1;
}


/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save_json(). The file may contain an array
  of length 0. Returns a pointer to a newly-allocated intarr_t on
  success (even if that array has length 0), or NULL on failure.

  Make sure you validate the parameter before you use it.
*/
intarr_t* intarr_load_json( const char* filename )
{
  FILE* f = fopen(filename, "r");
  if (f == NULL) 
  {
    return NULL;
  }
 
  intarr_t* loaded = intarr_create(0);
 
  int value;
  //Get rid of [
  fscanf(f, "%c ", &value);
  // Read the contents of the file line by line
  // Process each line.
  char line[100];
  while ( fgets(line, 100, f) )
  {
    if ( line[0] == ']' )
    {
       break;
    }
 
    if ( sscanf(line, "%d", &value) != 1 )
    {
       break;
    }
 
    // Use the number
    intarr_push(loaded, value);
  }
  
  fclose(f);
  return loaded;
}