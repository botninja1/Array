#include "array.h"

/*
 * Initialize a new Array.
 * @param init_size The initial size of the array.
 * @param init_type The size of the data type in the array.
 * @return The initialized Array struct.
 */
Array* array_init(size_t init_size, size_t init_type) {
    if (init_size == 0 || init_type == 0) {
        return NULL;
    }
    Array *memory = malloc(sizeof(Array));
    if(!memory) return NULL;
    *memory = (Array){
        .size = init_size,
        .type = init_type,
        .index = 0,
        .ptr = malloc(init_size * init_type),
    };
    if(!memory->ptr)
        free(memory);
        return NULL;
    return memory;
}


/**
 * Initializes a new Array with the specified elements, number of elements, and element size.
 * 
 * @param elements A pointer to the elements to be copied into the Array.
 * @param num_elements The number of elements in the provided array.
 * @param element_size The size (in bytes) of each element.
 * @return A pointer to the newly initialized Array.
 *         Returns NULL if the number of elements or element size is zero, or if memory allocation fails.
 */
Array* element_array_init(void *elements, size_t num_elements, size_t element_size) {
    if (num_elements == 0 || element_size == 0)
        return NULL;

    Array *memory = malloc(sizeof(Array));
    if (!memory) return NULL;

    memory->ptr = malloc(num_elements * element_size);
    if (!memory->ptr) {
        free(memory);
        return NULL;
    }

    memory->size = num_elements;
    memory->type = element_size;
    memory->index = num_elements;

    memcpy(memory->ptr, elements, num_elements * element_size);

    return memory;
}


/*
 * Expand the size of the array by adding a specified number of elements.
 * @param self Pointer to the Array struct to be expanded.
 * @param add_size Number of elements to add to the array.
 * @return true if the expansion is successful, false otherwise.
 */
bool expand_array(Array *self, const size_t add_size) {
     size_t new_size = (add_size + self->size) * self->type;

    void *temp_memory = realloc(self->ptr, new_size);

    if (temp_memory) {
        self->size = new_size/self->type;
        self->ptr = temp_memory;
        return true;  
    }

    return false; 
}


/*
 * Reduce the size of the array by removing a specified number of elements.
 * @param self Pointer to the Array struct to be reduced.
 * @param rm_size Number of elements to remove from the array.
 * @return true if the reduction is successful, false otherwise.
 */
bool reduce_array(Array *self, const size_t rm_size) {
    if (rm_size >= self->size) {
        free_array(self);
        return 1;
    }
    size_t new_size = (self->size - rm_size) * self->type;
    void *temp_memory = realloc(self->ptr, new_size);
    if (temp_memory) {
        self->size = new_size/self->type;
        self->ptr = temp_memory;
        if (self->size <= self->index)
            self->index = self->size;
        return 1;
    }
    return 0;
}

/*
 * Free the memory allocated for the array.
 * @param self Pointer to the Array struct to be freed.
 */
void free_array(Array *self) {
    if(!self || !self->ptr) return;
    free(self->ptr);
    self->ptr = NULL;
    self->index = 0;
    self->size = 0;
}


/*
 * Append an element to the array.
 * @param self Pointer to the Array struct (self-reference).
 * @param element Pointer to the element to be appended.
 * @return true if the append operation is successful, false otherwise.
 */
bool append(Array *self, const void *element) {
    if ((!self) || (!self->ptr) || (self->index >= self->size))
        return false;

    size_t offset = self->index * self->type;

    memcpy(((char *)self->ptr + offset), element, self->type);

    self->index += 1;

    return true;  
}


/*
 * Retrieve the element at a specific index in the array.
 * @param self Pointer to the Array struct (self-reference).
 * @param at Index of the element to retrieve.
 * @return Pointer to the retrieved element, or NULL if the index is out of bounds.
 */
void *get_element(Array *self, const size_t at) {
    if ((!self) || (!self->ptr) || ((self->index - 1) < at))
        return NULL;

    return ((char *)self->ptr + (at * self->type));
}


/*
 * Edit the element at a specific index in the array.
 * @param self Pointer to the Array struct (self-reference).
 * @param element Pointer to the new element value.
 * @param element_index Index of the element to edit.
 * @return true if the edit operation is successful, false otherwise.
 */
bool edit_at(Array *self, const size_t element_index, const void *element) {
    if ((!self) || (!self->ptr) || ((self->index - 1) < element_index))
        return false;

    size_t offset = element_index * self->type;
    memcpy(((char *)self->ptr + offset), element, self->type);

    return true; 
}


/**
 * Returns a pointer to the beginning of the data in the given Array.
 *
 * @param self Pointer to the Array.
 * @return Pointer to the beginning of the data.
 */
void *begin(Array *self){
    return self->ptr;
}


/**
 * Returns a pointer to the end of the data in the given Array.
 *
 * @param self Pointer to the Array.
 * @return Pointer to the end of the data.
 */
void *end(Array *self){
    return ((char*)self->ptr + ((self->index) * self->type));
}
