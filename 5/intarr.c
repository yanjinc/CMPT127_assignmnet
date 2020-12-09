/* 
 * intarr.c
 *
 * Provides a bounds-checked, resizable array of integers with
 * random-access and stack interfaces, and several utility functions
 * that operate on them.
 * 
 */

/* DO NOT CHANGE THIS FILE - YOUR CODE WILL BE COMPILED AGAINST THE
   ORIGINAL. NON-COMPILING CODE WILL FAIL ALL THE TASKS!

   FOR TASKS WITH MORE THAN ONE FUNCTION, YOU MUST IMPLEMENT ALL
   FUNCTIONS TO PASS THE TASK.
*/

#include <stdio.h>
#include <stdlib.h> // malloc()
#include <assert.h>
#include <string.h>

#include "intarr.h"


/* LAB 5 TASK 1 */

// Create a new intarr_t with initial size len.  If successful
// (i.e. memory allocation succeeds), returns a pointer to a
// newly-allocated intarr_t.  If unsuccessful, returns a null pointer.
intarr_t* intarr_create( unsigned int len )
{
  intarr_t* intarr_new = malloc( sizeof(intarr_t) );

  if( intarr_new == NULL )
  {
    printf( "Warning: failed to allocate memory\n" ); 
  }

  intarr_new->len = len;
  intarr_new->data = malloc( sizeof(int) * (intarr_new->len) );

  return intarr_new;
}

// Frees all memory allocated for ia. If the pointer is null, do
// nothing. If the ia->data is null, do not attempt to free it.
void intarr_destroy( intarr_t* ia )
{
  int* value = ia->data;

  if (ia == NULL || value == NULL)
  {
    exit(1);
  }

  free(ia);

  return;
}

/* LAB 5 TASK 2 */

// If index is valid, set the value at ia->data[index] to val and return
// INTARR_OK. Otherwise, leave the array unmodified and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_set( intarr_t* ia, 
							unsigned int index, 
							int val )
{

  if (index >= 0 && index < (ia->len)) 
  {    
    ia->data[index] = val;
    return INTARR_OK;
  } 
  else if (ia == NULL) 
  {
    return INTARR_BADARRAY;
  } 
  else 
  {
    return INTARR_BADINDEX;
  }

}

// If index is valid and val is non-null, set *val to ia->data[index] and return
// INTARR_OK. Otherwise do not modify *val and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_get( const intarr_t* ia, 
							unsigned int index, 
							int* val )
{

  if (index >= 0 && index < (ia->len) && val != NULL)
  {
    *val = ia->data[index];
    return INTARR_OK;
  } 
  else if (ia == NULL)
  {
    return INTARR_BADARRAY;
  } 
  else
  {
    return INTARR_BADINDEX;
  }
  
}

/* LAB 5 TASK 3 */

// Return a duplicate of ia, allocating new storage for the duplicate
// data (we call this a "deep copy"). If unsuccessful (i.e. memory
// allocation for the copy fails, or ia is null), return a null pointer. 
intarr_t* intarr_copy( const intarr_t* ia )
{
  intarr_t* ia_copy =  intarr_create(ia->len); 

  unsigned int numbytes = (ia->len) * sizeof(int);
  memcpy( ia_copy->data, ia->data, numbytes );

  if (ia_copy == NULL) 
  {
    printf( "Warning: failed to allocate memory\n" ); 
    return NULL;
  }

  return ia_copy;
}

/* LAB 5 TASK 4 */

// Sort ia by value smallest-to-largest, so that data[i] < data[i+1]
// for all valid i, then return INTARR_OK. Works in-place: contents of
// ia are sorted on return. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_sort( intarr_t* ia )
{
  if (ia == NULL) 
    return INTARR_BADARRAY;

  //SELECTION SORT
  int min, min_idx, temp; 
  for (unsigned int i=0; i<(ia->len); i++) {
    
    min = ia->data[i];
    min_idx = i;
    
    for (unsigned int j=i; j<(ia->len); j++) {
      if (ia->data[j] <= min) {
        min = ia->data[j];
        min_idx = j;
      }
    }

    temp = ia->data[i];
    ia->data[i] = min;
    ia->data[min_idx] = temp;

  }

  return INTARR_OK;
}

/* LAB 5 TASK 5 */

// Find the first occurrence of the target in the array, searching from
// index 0. If the target is found and i is non-null, set *i to the
// location index and return INTARR_OK. If target does not occur in
// the array, leave *i unmodified and return INTARR_NOTFOUND. If ia is
// null, return INTARR_BADARRAY.
intarr_result_t intarr_find( intarr_t* ia, int target, int* i )
{
  if (ia == NULL)
    return INTARR_BADARRAY;

  for (unsigned int j=0; j<(ia->len); j++) 
  {
    if (ia->data[j] == target && i != NULL) 
    {
      *i = j;
      return INTARR_OK;
    }
  }
  
  return INTARR_NOTFOUND;
}

/* LAB 5 TASK 6 */

// HINT: First, do TASK 7, since you will need to resize your array
//       by +1 in order to successfully push val.
// Append val to the end of ia (allocating space for it). If
// successful, return INTARR_OK, otherwise return
// INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_push( intarr_t* ia, int val )
{
  if (ia == NULL)
    return INTARR_BADARRAY;

  int origin_len = ia->len;
  int newlen = (ia->len) + 1;
  
  if (intarr_resize(ia, newlen) == INTARR_OK) 
  {
    ia->data[newlen-1] = val;
    return INTARR_OK;
  } 
  else 
  {
    return INTARR_BADALLOC;
  }

}

// HINT: You will need to decrement len so that it always represents
//       the number of int's stored in the array data.
// If the array is not empty, remove the value with the highest index
// from the array, and, if i is non-null, set *i to the removed value,
// then return INTARR_OK. If the array is empty, leave *i unmodified
// and return INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_pop( intarr_t* ia, int* i )
{
  unsigned int len = ia->len;
  if (ia==NULL)
  {
    return INTARR_BADARRAY;
  }

  if (len!=0 && i!=NULL){
    ia->data=realloc(ia->data,(sizeof(int)*(len)));
    
    if(ia->data!=NULL){
      *i = ia->data[len-1];
      ia->len--;
      return INTARR_OK;
    }
  }
  return INTARR_BADINDEX;
}

/* LAB 5 TASK 7 */

// HINT: Do this task before doing TASK 6.
// Resize ia to contain newlen values. If newlen is less than the
// original array length, the end of the array is discarded. 
// If newlen is greater than the original array length, the values 
// of the new integers will be undefined 
// (see https://en.cppreference.com/w/c/memory/realloc). 
// If the allocation is successful, return INTARR_OK, otherwise 
// return INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_resize( intarr_t* ia, unsigned int newlen )
{
  if (ia == NULL)
    return INTARR_BADARRAY;

  if (newlen > 0) 
  {
    int ia_len = ia->len;
    
    int* new_data = realloc(ia->data, newlen*sizeof(int));
    ia->len = newlen;
    ia->data = new_data;
    
    if (newlen > ia_len && new_data != NULL) {
      for (unsigned int i=ia_len; i<newlen; i++) 
      {
        ia->data[i] = 0;
      }
    }

    return INTARR_OK;
  }
  
  return INTARR_BADALLOC;
}

/* LAB 5 TASK 8 */

// Get a deep copy of a portion of ia from index 'first' to index 'last'
// inclusive. If successful, return a pointer to a newly-allocated
// intarr_t containing a copy of the specified section. If an error
// occurs, i.e. ia is null, 'first' or 'last' are out of bounds, 
// 'last' < 'first', or memory allocation fails, return a null pointer.
intarr_t* intarr_copy_subarray( intarr_t* ia, 
								unsigned int first, 
								unsigned int last )
{
  if (ia == NULL || first < 0 || last > (ia->len)-1 || last < first) 
    return NULL;

  //memory allocate
  intarr_t* intarr_new = malloc(sizeof(intarr_t));
  intarr_new->data = malloc((last-first+1)*sizeof(int));
  
  if (intarr_new->data == NULL) {
    printf("Warning: failed to allocate memory\n");
    exit(1);
  }

  intarr_new->len = last-first+1;
  for (unsigned int i=0; i<(last-first+1); i++) {
    intarr_new->data[i] = ia->data[i+first];
  }

  return intarr_new;
}