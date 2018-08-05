#include <stdio.h>
#include <string.h>
#include "ExploreDataType.h"

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (int i = 0; i < len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x){
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x){
    show_bytes((byte_pointer) &x, sizeof(void *));
}

void test_show_bytes(int val) {
    int ival = val;
    float fval = (float)val;
    int *pval = &ival;

    show_int(ival);
    show_float(fval);
    show_pointer(pval);

    const char *s = "abcdef";
    show_bytes((byte_pointer)s, strlen(s));
}


// little end machie
// 64 bits
// int main(int argc, char const *argv[])
// {
//     test_show_bytes(12345);
//     return 0;
// }