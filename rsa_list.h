#include <stdint.h>

#ifndef RSA_LIST_H
#define RSA_LIST_H

struct IntList {
    int size;
    int capacity;
    uint32_t arr[];
};

struct IntList *il_create_with_capacity(int capacity);
struct IntList *il_create(void);
void il_increase_capacity(struct IntList *list, int new_capacity);
void il_add_at_index(struct IntList *list, int index, uint32_t value);
void il_add(struct IntList *list, uint32_t value);
uint32_t il_get(struct IntList *list, int index);
uint32_t il_remove(struct IntList *list, int index);

#endif