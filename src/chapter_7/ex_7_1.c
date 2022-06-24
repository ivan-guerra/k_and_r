#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    (void)argc; /* Avoid unused parameter warning. */

    static const char *UPPER = "upper";
    static const char *LOWER = "lower";
    enum Action
    {
        TO_UPPER,
        TO_LOWER,
        ERROR
    };

    enum Action action = ERROR;
    if (strstr(argv[0], LOWER)) {
        action = TO_LOWER;
    } else if (strstr(argv[0], UPPER)) {
        action = TO_UPPER;
    } else {
        fprintf(stderr, "usage: [upper|lower]\n");
        fprintf(stderr, "if the exe is named ex_7_1, use mv to rename it: "
                        "'mv ex_7_1 [upper|lower]'\n");
        return -1;
    }

    int c = 0;
    while ((c = getchar()) != EOF) {
        switch (action) {
            case TO_LOWER:
                putchar(tolower(c));
                break;
            case TO_UPPER:
                putchar(toupper(c));
                break;
            default:
                fprintf(stderr, "error unknown action\n");
                return -1;
        }
    }

    return 0;
}
