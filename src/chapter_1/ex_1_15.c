#include <stdio.h>

float fahrenheit_to_celsius(float fahr)
{
    return (5.f / 9.f) * (fahr - 32.f);
}

int main()
{
    float fahr  = 0.f;
    int   upper = 300;
    int   step  = 20;

    printf("Fahrenheit-Celsius Table\n");
    while (fahr < upper) {
        printf("%3.0f %6.2f\n", fahr, fahrenheit_to_celsius(fahr));
        fahr = fahr + step;
    }

    return 0;
}
