#include <stdio.h>
#include "array.h"

#define SIZE_ARRAY 3
#define to_int(x) *((int*)(x))  // Cast pointer x to int* and dereference it to get the content
#define size_array(x, y) sizeof(x)/sizeof(y)

int main() {
    // Initialize an Array with a specific size and element type
    Array *arr = array_init(SIZE_ARRAY, sizeof(int));
    size_t index = 0;

    // Populate the Array with elements using the append function
    for(index = 0; i < arr->size; index++) {
        if (!append(arr, &index)) {
            fprintf(stderr, "[!] Overflow Append [!]");
            return -1;
        }
    }

    // Expand the size of the Array by 1
    if (!expand_array(arr, 1)) {
        fprintf(stderr, "[!] Error Expand Array [!]");
        return -1;
    }

    // Print the elements after expansion
    printf("Expand Array:\n");
    for(int i = 0; i < (arr->index); i++) {
        printf("arr[%d]: %d\n", i, to_int(get_element(arr, i))); //I use get_element(arr, i) function to show the usage
    }

    // Reduce the size of the Array by 2
    if (!reduce_array(arr, 2)) {
        fprintf(stderr, "[!] Error Reduce Array [!]");
        return -1;
    }
    // Print the elements after reduction
    printf("Reduce Array:\n");
    index = 0;
    for(int *it = begin(arr); it != end(arr); it++) {
        printf("arr[%d]: %d\n", index, *it);
        index++;
    }


    // Edit an element at a specific index
    int el = 10;
    index = 0;
    printf("Edit At:\n");
    if (edit_at(arr, index, &el)) {
        printf("arr[%d]: %d\n", index, to_int(get_element(arr, index)));
    }

    // Initialize a new Array with specified elements
    int initial_elements[] = {99, 2, 3};
    Array *buffer = element_array_init(initial_elements, size_array(initial_elements, int), sizeof(int));

    // Iterate over the elements in the buffer Array
    index = 0;
    printf("Iterator over the buffer:\n");
    for(int *it = begin(buffer); it != end(buffer); it++) {
        printf("arr[%d]: %d\n", index, *it);
        index++;
    }

    // Free the memory allocated for both Arrays
    free_array(arr);
    free(arr);

    return 0;
}
