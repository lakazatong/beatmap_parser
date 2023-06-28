// Source: ChatGPT

#include "list.h"

List new_list(int initial_capacity) {
	List list;
	list.elements = malloc(initial_capacity * sizeof(void*));
	if (list.elements == NULL) {
		// Error handling - failed to allocate memory
		printf("Failed to allocate memory for list.\n");
		list.size = 0;
		list.capacity = 0;
		return list;
	}
	for (int i = 0; i < initial_capacity; i++) {
		list.elements[i] = NULL;
	}
	list.size = 0;
	list.capacity = initial_capacity;
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
	list->elements[list->size] = element;
	list->size++;
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