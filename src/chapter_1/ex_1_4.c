
#include <stdio.h>

int main()
{
    float fahr    = 0.f;
    float celsius = 0.f;
    int lower = 0;
    int upper = 300;
    int step  = 20;

    printf("Celsius-Fahrenheit Table\n");
    celsius = lower;
    while (celsius < upper) {
        fahr = (9.f/ 5.f) * celsius + 32.f;
        printf("%3.0f %6.2f\n", celsius, fahr);
        celsius = celsius + step;
    }

    return 0;
}
