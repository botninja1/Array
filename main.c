#include <stdio.h>
#include "array.h"

#define SIZE_ARRAY 3

int main(){
    Array *arr = array_init(SIZE_ARRAY, sizeof(int));

    for(int i=0; i<arr->size; i++){
        if(!append(arr, &i)){
            fprintf(stderr, "[!] Overflow Append [!]");
            return -1;
        }
    }
    if(!expand_array(arr, 1)){
        fprintf(stderr, "[!] Error Expand Array [!]");
        return -1;
    }
    printf("Expand Array:\n");
    for(int i = 0; i < (arr->index); i++){
        printf("%d\n", *((int*)get_element(arr, i)));
    }
    if(!reduce_array(arr, 2)){
        fprintf(stderr, "[!] Error Reduce Array [!]");
        return -1;
    }

    printf("Reduce Array:\n");
    for(int i = 0; i < (arr->index); i++){
        printf("%d\n", *((int*)get_element(arr, i)));
    }
    free_array(arr);
    
    free(arr);
    return 0;
}
