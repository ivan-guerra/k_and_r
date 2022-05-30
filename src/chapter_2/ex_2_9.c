#include <stdio.h>

/*!
 * \brief Return the number of high bits in \a x.
 */
int bitcount(unsigned x);

int main()
{
    unsigned x = 42;
    printf("x = %#x\n", x);
    printf("bitcount(x) = %d\n", bitcount(x));

    return 0;
}

int bitcount(unsigned x)
{
    int count = 0;
    while (x) {
        x &= (x - 1);
        count++;
    }

    return count;
}
