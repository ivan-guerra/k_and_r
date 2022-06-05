#include <stdio.h>


#define swap(t,x,y)\
{                  \
    t tmp = x;     \
    x = y;         \
    y = tmp;       \
}

int main(void)
{
    double x = 53.24;
    double y = 78.99;
    printf("BEFORE:\n\tx = %g\n\ty = %g\n", x, y);
    swap(double, x, y);
    printf("AFTER:\n\tx = %g\n\ty = %g\n", x, y);

    return 0;
}
