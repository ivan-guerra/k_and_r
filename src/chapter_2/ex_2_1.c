#include <stdio.h>
#include <limits.h>


int main()
{
    printf("\t=== Data Type Ranges ===\n");
    printf("char           -> [%d, %d]\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char  -> [%d, %d]\n", 0, UCHAR_MAX);

    printf("short          -> [%d, %d]\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short -> [%d, %d]\n", 0, USHRT_MAX);

    printf("int            -> [%d, %d]\n", INT_MIN, INT_MAX);
    printf("unsigned int   -> [%u, %u]\n", 0, UINT_MAX);

    printf("long           -> [%ld, %ld]\n", LONG_MIN, LONG_MAX);
    printf("unsigned long  -> [%lu, %lu]\n", 0UL, ULONG_MAX);

    return 0;
}
