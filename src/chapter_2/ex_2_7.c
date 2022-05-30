#include <stdio.h>

/*!
 * \brief Get the \a n bits starting at position \a p in \a x.
 */
unsigned getbits(unsigned x, int p, int n);

/*!
 * \brief Invert the \a n bits starting at position \a p in \a x.
 */
unsigned invert(unsigned x, int p, int n);

int main()
{
    unsigned x = 0x78;
    int      p = 6;
    int      n = 4;
    printf("x = %#x\n", x);
    printf("p = %d\n", p);
    printf("n = %d\n", n);
    printf("invert(x, p, n) = %#x\n", invert(1, 4, 3));

    return 0;
}

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0U << n);
}

unsigned invert(unsigned x, int p, int n)
{
    /* Create a mask with the n bits at position p in x inverted. */
    unsigned inverted_bit_mask = (~getbits(x, p, n) & ~(~0U << n)) << p;

    /* Create a mask that can be used to clear the n bits at position p in x. */
    unsigned clear_mask = ~(~(~0U << n) << p);

    return (x & clear_mask) | inverted_bit_mask;
}
