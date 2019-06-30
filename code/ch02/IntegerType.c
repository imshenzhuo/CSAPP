#include <stdio.h>  
#include "ExploreDataType.h"

void Tcode(){
    short x = 12345;
    short mx = -x;

    show_bytes((byte_pointer) &x, sizeof(short));
    show_bytes((byte_pointer) &mx, sizeof(short));

}

void sign2unsign() {
    short int v = -12345;
    unsigned short uv = (unsigned short) v;
    printf("v = %d, uv = %u\n", v, uv);
}

float sum_elements(float a[], unsigned length) {
    show_bytes((byte_pointer) &length, sizeof(unsigned));
    unsigned tmp = length - 1;
    show_bytes((byte_pointer) &tmp, sizeof(unsigned));
    int tmp_int = (int)tmp;
    show_bytes((byte_pointer) &tmp_int, sizeof(int));
    printf("tmp_int is %d\n", tmp_int);
    printf("length of unsigned is %lu\n", sizeof(unsigned));
    int i;
    float result = 0;
    for (int i = 0; i <= length-1; ++i) {
        result += a[i];
    }
    return result;
}

void sign_unsign_buggy_code() {
    float a[] = {};
    unsigned length = 0;
    printf("%f\n", sum_elements(a, length));
    sum_elements(a, length);
}




int main(int argc, char const *argv[])
{
    // Tcode();
    // sign2unsign();
    sign_unsign_buggy_code();
    return 0;
}