// list.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// returns a pointer to a new header for an empty list, or NULL if
// memory allocation fails.
list_t* list_create(void) {
  list_t* newList = malloc(sizeof(list_t));
  if (newList) {
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
  } else {
    return NULL;
  }
}

// frees all the memory used by the list
void list_destroy(list_t* list) {
  element_t* temp = list->head;
  element_t* next;
  printf("\nfreeing : ");
  while (temp) {
    next = temp->next;
    printf("%d ", temp->val);
    free(temp);
    temp = next;
  }
  list->head = NULL;
  list->tail = NULL;
}

// returns a pointer to a new list element containing integer i and
// next-pointer set to NULL, or NULL if memory allocation fails.
element_t* element_create(int i) {
  element_t* newElement = malloc(sizeof(element_t));
  if (newElement) {
    newElement->val = i;
    newElement->next = NULL;
  } else {
    return NULL;
  }
}

// Appends a new element containing integer i to the end of the
// list. Returns 0 on success, else 1.
int list_append(list_t* list, int i) {
  element_t* temp = element_create(i);
  if (temp)
    if (list->head == NULL && list->tail == NULL) {
      list->head = temp;
      list->tail = list->head;
      return 0;
    } else {
      list->tail->next = temp;
      list->tail = list->tail->next;
      return 0;
    }
  else
    return 1;
}

// Prepends a new element containing integer i to the head of the
// list. Returns 0 on success, else 1.
int list_prepend(list_t* list, int i) {
  element_t* temp = element_create(i);
  if (temp)
    if (list->head == NULL && list->tail == NULL) {
      list->head = temp;
      list->tail = list->head;
      return 0;
    } else {
      temp->next = list->head;
      list->head = temp;
      return 0;
    }
  else
    return 1;
}

// Returns a pointer to the ith list element, where the list head is
// 0, head->next is 1, etc., or NULL if i is out of range (i.e. larger
// than (number of list elements -1 ))
element_t* list_index(list_t* list, unsigned int i) {
  int count = 0;
  element_t* temp = list->head;
  while (temp) {
    if (count == i)
      return temp;
    else
      temp = temp->next;
    count++;
  }
  return NULL;
}

// Prints a list in human-readable form from the first to last
// elements, between curly braces.
void list_print(list_t* list) {
  element_t* temp = list->head;
  printf("{ ");
  while (temp) {
    printf("%d ", temp->val);
    temp = temp->next;
  }
  printf("}\n");
}