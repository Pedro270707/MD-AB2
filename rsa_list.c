#include <stddef.h>
#include <stdlib.h>
#include "rsa_list.h"

struct IntList *il_create_with_capacity(int capacity) {
    struct IntList *list = (struct IntList *) malloc(sizeof(struct IntList) + capacity * sizeof(uint32_t));

    if (list == NULL) {
        return NULL;
    }

    list->size = 0;
    list->capacity = capacity;

    return list;
}

struct IntList *il_create() {
    return il_create_with_capacity(1);
}

void il_increase_capacity(struct IntList *list, int new_capacity) {
    if (new_capacity <= list->capacity) {
        return;
    }
    list->capacity = new_capacity;
}

void il_add_at_index(struct IntList *list, int index, uint32_t value) {
    if (index < 0 || index > list->size) {
        return;
    }
    if (index < list->size) {
        for (int i = list->size - 1; i > index; i--) {
            list->arr[i] = list->arr[i - 1];
        }
    }
    list->arr[index] = value;
    list->size++;
    if (list->size == list->capacity) {
        il_increase_capacity(list, (int) (list->capacity * 1.25) + 1);
    }
}

void il_add(struct IntList *list, uint32_t value) {
    il_add_at_index(list, list->size, value);
}

uint32_t il_get(struct IntList *list, int index) {
    if (index < 0 || index >= list->size) {
        return 0;
    }
    return list->arr[index];
}

uint32_t il_remove(struct IntList *list, int index) {
    if (index < 0 || index >= list->size) {
        return -1;
    }
    uint32_t previous_value = list->arr[index];
    for (int i = list->size - 1; i >= index; i--) {
        list->arr[i] = list->arr[i - 1];
    }
    list->size--;
}