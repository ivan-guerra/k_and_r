#include <stdio.h>

int main()
{
    float fahr    = 0.f;
    float celsius = 0.f;
    int lower = 0;
    int upper = 300;
    int step  = 20;

    printf("Fahrenheit-Celsius Table\n");
    fahr = lower;
    while (fahr < upper) {
        celsius = (5.f/ 9.f) * (fahr - 32.f);
        printf("%3.0f %6.2f\n", fahr, celsius);
        fahr = fahr + step;
    }

    return 0;
}
