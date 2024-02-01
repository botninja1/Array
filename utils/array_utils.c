#include "array_utils.h"

void* my_memcpy(void *dest, const void *src, size_t count){
    char *dest_ptr = dest;
    const char *src_ptr = src;

    while(count--){
        *dest_ptr++ = *src_ptr++;
    }
    return dest;
}