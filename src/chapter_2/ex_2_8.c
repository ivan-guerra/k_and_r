#include <stdio.h>

/*!
 * \brief Rotate bits in \a x by \a n bits to the right.
 */
unsigned rightrot(unsigned x, int n);

int main()
{
    unsigned x = 0xf;
    int      n = 4;
    printf("x = %#x\n", x);
    printf("n = %d\n", 4);
    printf("rightrot(x, n) = %#x\n", rightrot(x, n));

    return 0;
}

unsigned rightrot(unsigned x, int n)
{
    /* Retrieve the lowest n bits in x. */
    int lowest_n_bits = ~(~0U << n) & x;

    /* Shift x n bits to the right, this is part I of the rotation. */
    x = x >> n;

    /* Part II of the roation is to place the lowest_n_bits at the highest
       position in the now shifted x. */
    return (x | (lowest_n_bits << (sizeof(x) * 8 - n)));
}
