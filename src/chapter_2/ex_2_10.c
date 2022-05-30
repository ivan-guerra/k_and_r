#include <stdio.h>

int lower(int c);

int main()
{
    const char *ALL_CAPS_WORD = "HELLO";
    for (size_t i = 0; ALL_CAPS_WORD[i]; ++i)
        printf("%c", lower(ALL_CAPS_WORD[i]));
    printf("\n");

    return 0;
}

int lower(int c)
{
    return ((c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c);
}
