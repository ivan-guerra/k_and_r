#include <stdio.h>

/*!
 * \brief Set \a n bits of \a x starting at position \a p to the rightmost
 *        \a n bits of \a y.
 */
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
    unsigned x = 42;
    unsigned y = 3;
    int      n = 2;
    int      p = 4;
    printf("x = %#x\n", x);
    printf("y = %#x\n", y);
    printf("n = %d\n", n);
    printf("p = %d\n", p);
    printf("setbits(x, p, n, y) = %#x\n", setbits(x, p, n, y));

    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    /* Fetch the rightmost n bits of y. */
    int righthand_bits = y & ~(~0U << n);

    /* Clear the n bits starting at position p in x. */
    x = x & ~(~(~0U << n) << p);

    /* Set the n bits at position p to the value of the n bits contained in
       righthand_bits. */
    return (x | (righthand_bits << p));
}
