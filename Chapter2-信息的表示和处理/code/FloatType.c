#include <stdio.h>

void testFloat() {
    double a = 0.33333333 ;
    printf("%lf\n", a*3);

    double b = 1.0 / 5;
    printf("%lf\n", b);
}

int main(int argc, char const *argv[])
{
    testFloat();
    return 0;
}