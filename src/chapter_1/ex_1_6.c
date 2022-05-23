#include <stdio.h>

int main()
{
    printf("Enter any character other than EOF: ");
    printf("\t(getchar() == EOF) = %d\n", (getchar() == EOF));

    /* Consume lingering newline. */
    getchar();

    printf("Enter EOF (ctrl-d):\n");
    printf("\t(getchar() == EOF) = %d\n", (getchar() == EOF));

    return 0;
}
