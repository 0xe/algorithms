#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "karatsuba.h"

int main() {
    int64_t x = 5678321;
    int64_t y = 1234655;
    int64_t mul;

    clock_t start, end; double cpu_time;

    start = clock();
    mul = karatsuba(x, y);
    end = clock();
    cpu_time = ((double) (end - start) / CLOCKS_PER_SEC);
    printf("karatsuba %lld %fms\n", mul, cpu_time*1000);

    start = clock();
    mul = x * y;
    end = clock();
    cpu_time = ((double) (end - start) / CLOCKS_PER_SEC);
    printf("normal %lld %fms\n", mul, cpu_time*1000);
}