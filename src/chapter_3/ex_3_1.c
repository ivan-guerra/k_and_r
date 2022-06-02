#define _XOPEN_SOURCE 700 /* Used to make sure we get time.h features. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STEP_SIZE    100
#define MAX_ARR_SIZE 1000000

int binsearch(int x, int v[], int n);
int binsearch_mod(int x, int v[], int n);

/*!
 * \brief Initialize \a v with values in ascending order in the range [1, n].
 *
 * It is assumed \a v is large enough to hold \a n elements.
 */
void populate_array(int v[], size_t n);

/*!
 * \brief Return the delta (t1 - t2) in microseconds.
 */
long get_timediff_nsec(const struct timespec *t1, const struct timespec *t2);

/*!
 * \brief Return the average of the time deltas in \a deltas_nsec.
 */
float compute_avg_time_delta(const int *deltas_nsec, size_t n);

int main()
{
    /* timespec structs used to capture bsearch execution start/end time. */
    struct timespec start, end, start_mod, end_mod;

    /* Arrays used to store the execution times of each bsearch variant in
       microseconds. */
    int timediffs[MAX_ARR_SIZE / STEP_SIZE]     = {0};
    int timediffs_mod[MAX_ARR_SIZE / STEP_SIZE] = {0};

    int key = 0;                    /* Current bsearch search key. */
    int values[MAX_ARR_SIZE] = {0}; /* Array of sorted values. */
    size_t i, j;
    for (i = STEP_SIZE, j = 0; i < MAX_ARR_SIZE; i += STEP_SIZE, ++j) {
        /* Populate the values array with i integers in [1, i]. */
        populate_array(values, i);

        /* Generate a random search key in the range [1, i]. */
        key = (rand() % i) + 1;

        /* Measure the execution time of each binary search variant. */
        clock_gettime(CLOCK_MONOTONIC, &start);
        binsearch(key, values, i);
        clock_gettime(CLOCK_MONOTONIC, &end);
        timediffs[j] = get_timediff_nsec(&end, &start);

        clock_gettime(CLOCK_MONOTONIC, &start_mod);
        binsearch_mod(key, values, i);
        clock_gettime(CLOCK_MONOTONIC, &end_mod);
        timediffs_mod[j] = get_timediff_nsec(&end_mod, &start_mod);
    }

    /* Print the average execution of each binary search variant. */
    printf("binsearch average time delta     = %0.4f nsec\n",
           compute_avg_time_delta(timediffs, MAX_ARR_SIZE / STEP_SIZE));
    printf("binsearch_mod average time delta = %0.4f nsec\n",
           compute_avg_time_delta(timediffs_mod, MAX_ARR_SIZE / STEP_SIZE));

    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int binsearch_mod(int x, int v[], int n)
{
    int low  = 0;
    int high = n - 1;
    int mid  = 0;
    while ((low <= high) && (v[mid] != x)) {
        mid = (low + high) / 2;
        if (x > v[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }
    return (v[mid] == x) ? mid : -1;
}

void populate_array(int v[], size_t n)
{
    if ((0 == n) || !v)
        return;

    for (size_t i = 0; i < n; ++i)
        v[i] = i + 1;
}

long get_timediff_nsec(const struct timespec *t1, const struct timespec *t2)
{
    static const long SEC_TO_NSEC = 1000000000L;
    long t1_nsec = t1->tv_sec * SEC_TO_NSEC + t1->tv_nsec;
    long t2_nsec = t2->tv_sec * SEC_TO_NSEC + t2->tv_nsec;

    return (t1_nsec - t2_nsec);
}

float compute_avg_time_delta(const int *deltas_nsec, size_t n)
{
    if ((0 == n) || !deltas_nsec)
        return 0.f;

    float avg = 0.f;
    for (size_t i = 0; i < n; ++i)
        avg += deltas_nsec[i] / (float)n;

    return avg;
}
