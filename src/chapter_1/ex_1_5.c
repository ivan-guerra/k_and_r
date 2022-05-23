#include <stdio.h>

int main()
{
    for (int fahr = 300; fahr >= 0; fahr = fahr - 20)
        printf("%3d %6.1f\n", fahr, (5.f / 9.f) * (fahr - 32.f));

    return 0;
}
