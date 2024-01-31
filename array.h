#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    void *ptr;
    size_t size;
    size_t index;
    size_t type;
} Array;

Array* array_init(size_t init_size, size_t init_type);
bool expand_array(Array *arr, const size_t add_size);
bool reduce_array(Array *arr, const size_t rm_size);
void free_array(Array *arr);
bool append(Array *arr, const void *element);
void *get_element(Array *arr, const size_t at);
bool edit_at(Array *arr, const void *element, const size_t element_index);

#endif  // ARRAY_H
