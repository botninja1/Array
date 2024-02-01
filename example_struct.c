#include <stdio.h>
#include "array.h"

#define SIZE_ARRAY 3
#define to_example(x) *((Example*)x)  //I cast X into pointer to Example with (Example*) and then take the content it points to by putting *((Example*))

typedef struct example{
    int x;
    int j;
    char c;
}Example;

int main(){
    Array *arr = array_init(SIZE_ARRAY, sizeof(Example));
    for(int i=0; i<arr->size; i++){
        Example tr = (Example){
            .x = i+i,
            .j = i*i,
            .c = 'a',
        };
        if(!append(arr, &tr)){
            fprintf(stderr, "[!] Overflow Append [!]");
            return -1;
        }
    }

    for(int i=0; i<arr->index; i++){
        Example temp = to_example(get_element(arr, i));
        printf("Struct n.%d:\n\nx = %d\nj = %d\nc = %c\n\n", i, temp.x, temp.j, temp.c);
    }

    free_array(arr);
    free(arr);
    return 0;
}
