// Source: ChatGPT

#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	void** elements;
	int size;
	int capacity;
} List;

typedef struct {
	int* elements;
	int size;
	int capacity;
} iList;

typedef struct {
	double* elements;
	int size;
	int capacity;
} dList;

typedef struct {
	char** elements;
	int size;
	int capacity;
} sList;

List* new_list(int initial_capacity);
void list_add(List* list, void* element);
void* list_pop(List* list, int index);
void free_list(List* list);

iList* new_ilist(int initial_capacity);
void ilist_add(iList* list, int element);
int ilist_pop(iList* list, int index);
void free_ilist(iList* list);

dList* new_dlist(int initial_capacity);
void dlist_add(dList* list, int element);
int dlist_pop(dList* list, int index);
void free_dlist(dList* list);

sList* new_slist(int initial_capacity);
void slist_add(sList* list, char* element);
char* slist_pop(sList* list, int index);
void free_slist(sList* list);
void destroy_slist(sList* list);

#endif