// Source: ChatGPT

#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	void** elements;
	int size;
	int capacity;
} List;

List new_list(int initial_capacity);
void list_add(List* list, void* element);
void* list_pop(List* list, int index);

#endif