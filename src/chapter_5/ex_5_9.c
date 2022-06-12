#include <stdio.h>

#define ROWS 2
#define COLS 13

static char daytab[ROWS][COLS] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main(void)
{
    int year, month, day, yearday;

    for (year = 1970; year <= 2000; ++year) {
        for (yearday = 1; yearday < 366; ++yearday) {
            if (month_day(year, yearday, &month, &day) == -1) {
                printf("month_day failed: %d %dn",
                        year, yearday);
            } else if (day_of_year(year, month, day) != yearday) {
                printf("bad result: %d %dn", year, yearday);
                printf("month = %d, day = %dn", month, day);
            }
        }
    }

    return 0;
}

int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    for (i = 1; i < month; ++i)
        day += *(*(daytab + leap) + i);
    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    for (i = 1; yearday > *(*(daytab + leap) + i); ++i)
        yearday -= *(*(daytab + leap) + i);

    *pmonth = i;
    *pday   = yearday;

    return 0;
}
