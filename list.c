// Source: ChatGPT

#include "list.h"

List* new_list(int initial_capacity) {
	List* list = malloc(sizeof(List));
	list->elements = malloc(initial_capacity * sizeof(void*));
	if (list->elements == NULL) {
		// Error handling - failed to allocate memory
		printf("Failed to allocate memory for list.\n");
		list->size = 0;
		list->capacity = 0;
		return list;
	}
	for (int i = 0; i < initial_capacity; i++) {
		list->elements[i] = NULL;
	}
	list->size = 0;
	list->capacity = initial_capacity;
	return list;
}

void list_add(List* list, void* element) {
	if (list->size >= list->capacity) {
		int new_capacity = (list->capacity == 0) ? 1 : 2 * list->capacity;
		void** new_elements = realloc(list->elements, new_capacity * sizeof(void*));
		if (new_elements == NULL) {
			// Error handling - failed to allocate memory
			printf("Failed to allocate memory for list.\n");
			return;
		}
		for (int i = list->capacity; i < new_capacity; i++) {
			new_elements[i] = NULL;
		}
		list->elements = new_elements;
		list->capacity = new_capacity;
	}
	list->elements[list->size++] = element;
}

void* list_pop(List* list, int index) {
	if (index < 0 || index >= list->size) {
		// Error handling - index out of bounds
		printf("Index out of bounds.\n");
		return NULL;
	}
	void* element = list->elements[index];
	for (int i = index; i < list->size - 1; i++) {
		list->elements[i] = list->elements[i + 1];
	}
	list->size--;
	return element;
}

void free_list(List* list){
	free(list->elements);
	free(list);
}

iList* new_ilist(int initial_capacity) {
	iList* list = malloc(sizeof(iList));
	list->elements = malloc(initial_capacity * sizeof(int));
	if (list->elements == NULL) {
		printf("Failed to allocate memory for iList.\n");
		list->size = 0;
		list->capacity = 0;
		return list;
	}
	list->size = 0;
	list->capacity = initial_capacity;
	return list;
}

void ilist_add(iList* list, int element) {
	if (list->size >= list->capacity) {
		int new_capacity = (list->capacity == 0) ? 1 : 2 * list->capacity;
		int* new_elements = realloc(list->elements, new_capacity * sizeof(int));
		if (new_elements == NULL) {
			printf("Failed to allocate memory for iList.\n");
			return;
		}
		list->elements = new_elements;
		list->capacity = new_capacity;
	}
	list->elements[list->size++] = element;
}

int ilist_pop(iList* list, int index) {
	if (index < 0 || index >= list->size) {
		printf("Index out of bounds.\n");
		return -1;
	}
	int element = list->elements[index];
	for (int i = index; i < list->size - 1; i++) {
		list->elements[i] = list->elements[i + 1];
	}
	list->size--;
	return element;
}

void free_ilist(iList* list) {
	free(list->elements);
	free(list);
}

sList* new_slist(int initial_capacity) {
	sList* list = malloc(sizeof(sList));
	list->elements = malloc(initial_capacity * sizeof(char*));
	if (list->elements == NULL) {
		printf("Failed to allocate memory for slist.\n");
		list->size = 0;
		list->capacity = 0;
		return list;
	}
	list->size = 0;
	list->capacity = initial_capacity;
	return list;
}

void slist_add(sList* list, const char* element) {
	if (list->size >= list->capacity) {
		int new_capacity = (list->capacity == 0) ? 1 : 2 * list->capacity;
		char** new_elements = realloc(list->elements, new_capacity * sizeof(char*));
		if (new_elements == NULL) {
			printf("Failed to allocate memory for slist.\n");
			return;
		}
		list->elements = new_elements;
		list->capacity = new_capacity;
	}
	list->elements[list->size] = malloc((strlen(element) + 1) * sizeof(char));
	strcpy(list->elements[list->size], element);
	list->size++;
}

char* slist_pop(sList* list, int index) {
	if (index < 0 || index >= list->size) {
		printf("Index out of bounds.\n");
		return NULL;
	}
	char* element = list->elements[index];
	for (int i = index; i < list->size - 1; i++) {
		list->elements[i] = list->elements[i + 1];
	}
	list->size--;
	return element;
}

void free_slist(sList* list) {
	free(list->elements);
	free(list);
}

void destroy_slist(sList* list){
	for (int i = 0; i < list->size; i++) free(list->elements[i]);
	free_slist(list);
}