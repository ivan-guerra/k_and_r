#include <stdio.h>
#include <stdlib.h>

/* Saves since you are not actually making a function call each time you
   'call' isupper_save_time in your code. However, you do use more space
   in the sense that your binary/code grows everytime you call the macro. */
#define isupper_save_time(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0

/* Saves space since the function is compiled into a single definition. There
   is some overhead to making function calls so this is slower than the
   macro. */
static int isupper_save_space(int c)
{
    return ((c >= 'A') && (c <= 'Z')) ? 1 : 0;
}

int main(void)
{
    exit(EXIT_SUCCESS);
}
