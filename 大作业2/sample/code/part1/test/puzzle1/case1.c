#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint64_t a = 0;

uint64_t __attribute__((noinline)) func(uint64_t x)
{
    if (x > 100)
        x = rand() % 100;
    else if (x > 10)
        x = (rand() + rand()) % 10;
    else
        x = 0;
    return x;
}

int __attribute__((noinline)) main()
{
    a = func(50);
    return 0;
}