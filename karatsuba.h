#ifndef __KARATSUBA_H
#define __KARATSUBA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

size_t count_digits(int64_t num)
{
    size_t num_digits = 0;

    // compute number of digits
    {
        int i = 0, n = num, q = 0;
        while ((q = (n / 10)) != 0) { i++; n = q; }
        num_digits = i + 1;
    }

    return num_digits;
}

void split(int64_t num, size_t size, int64_t *l, int64_t *r)
{
    size_t mid = size / 2;

    // compute left and right
    {
        size_t i = size;
        int64_t rem = num;

        while (i > mid) {
            int64_t dp = powl(10, i-1);
            rem = num - (num / dp) * dp;
            i = i-1;
        }

        *r = rem;
        *l = (num - rem) / powl(10, mid);
    }
}

int64_t karatsuba(int64_t x, int64_t y)
{
    size_t num_digits1 = count_digits(x);
    size_t num_digits2 = count_digits(y);

    size_t num = num_digits1 > num_digits2 ? num_digits1 : num_digits2;
    size_t mid = num / 2;

    if (num < 5) // arbitrary base case
        return x * y;

    int64_t a, b, c, d, k0, k1, k2;
    split(x, num, &a, &b);
    split(y, num, &c, &d);

    k0 = karatsuba(b, d);
    k1 = karatsuba(b + a, d + c);
    k2 = karatsuba(a, c);

    return (powl(10, mid * 2) * k2) + ((k1 - k2 - k0) * powl(10, mid)) + k0;
}

#endif // __KARATSUBA_H