#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "list.h"

int main( int argc, char* argv[] )
{
  // test the create function
  list_t* list = list_create();

  // check to see if the create function did everything it was supposed to
  if( list == NULL )
    {
      printf( "create: create failed to malloc\n" );
      return 1;
    }

  if( list->head != NULL )
    {
      printf( "create: head is not null!\n" );
      return 1;
    }

  if( list->tail != NULL )
    {
      printf( "create: tail is not null!\n" );
      return 1;
    }

  // now test all the other functions (except list_print) to see if
  // they do what they are supposed to

  // you code goes here
  
  // testing the list_prepend()
  int val = 26;
  int ret = list_prepend(list, 26);

  // list_prepend returns 0 on success, else 1
  if (ret) {
    puts("list_prepend() failed.");
    return 1;
  }
  if (list->head == NULL) {
    puts("list_prepend(): list->head NULL.");
    return 1;
  }
  if (list->tail == NULL) {
    puts("list_prepend(): list->tail NULL.");
    return 1;
  }
  if (list->head != list->tail) {
    puts("list_prepend(): first prepend: head != tail.");
    return 1;
  }
  if (list->head->next != NULL) {
    puts("list_prepend(): list->head->next != NULL.");
    return 1;
  }
  if (list->head->val != val) {
    puts("list_prepend(): list->head->val != val.");
    return 1;
  }

  // testing element_create()
  element_t* el = malloc(sizeof(element_t));
  assert(el);
  memset(el, 0xFF, sizeof(element_t));
  free(el);

  el = element_create(1492);
  assert(el);

  if (el->next) {
    puts("element_create(): el->next not NULL.");
    return 1;
  }

  if (el->val != 1492) {
    puts("element_create(): el->val not correct.");
    return 1;
  }

  // testing list_append
  int val2 = 37;
  int ret2 = list_append(list, 37);

  // returns 0 on success, else 1.
  if (ret2) {
    puts("list_append() failed.");
    return 1;
  }
  if (list->head == NULL) {
    puts("list_append(): list->head NULL.");
    return 1;
  }
  if (list->tail == NULL) {
    puts("list_append(): list->tail NULL.");
    return 1;
  }
  if (list->head == list->tail) {
    puts("list_append(): head == tail.");
    return 1;
  }
  if (list->tail->next != NULL) {
    puts("list_append(): list->tail->next != NULL.");
    return 1;
  }
  if (list->tail->val != val2) {
    puts("list_append(): list->tail->val != val1.");
    return 1;
  }

  // testing list_index
  list_t* l2 = list_create();

  element_t* el2 = list_index(l2, 1);
  // t1, t3: list->head == NULL
  if (el2 != NULL) {
    puts("list_index(): el2 != NULL.");
    return 1;
  }

  element_t* el3 = list_index(list, 3);
  if (el3 != NULL) {
    puts("list_index(): el3 nor correct.");
    return 1;
  }
  


  return 0; // tests pass
}
