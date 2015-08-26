#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

uint32_t clz1(uint32_t x) {
    uint32_t n;
    if (x == 0) return 32;
    n = 1;
    if ((x >> 16) == 0) { n += 16; x <<= 16; }
    if ((x >> 24) == 0) { n += 8; x <<= 8; }
    if ((x >> 28) == 0) { n += 4; x <<= 4; }
    if ((x >> 30) == 0) { n += 2; x <<= 2; }
    n = n - (x >> 31);
    return n;
}

#define u 0  /* don't care */
uint32_t clz2(uint32_t x) {
    static uint8_t table[64] = {
        32, 31,  u, 16,  u, 30,  3,  u, 15,  u,  u,  u, 29, 10,  2,  u,
         u,  u, 12, 14, 21,  u, 19,  u,  u, 28,  u, 25,  u,  9,  1,  u,
        17,  u,  4,  u,  u,  u, 11,  u, 13, 22, 20,  u, 26,  u,  u, 18,
         5,  u,  u, 23,  u, 27,  u,  6,  u, 24,  7,  u,  8,  u,  0,  u,
     };
     x = x | (x >> 1);
     x = x | (x >> 2);
     x = x | (x >> 4);
     x = x | (x >> 8);
     x = x | (x >> 16);
     x *= 116069625; // Multiplier is H
     return table[x >> 26];
 } 

int main()
{
    uint32_t x;
    clock_t start1, start2, end1, end2;

    start1 = clock();
    for( x = 0; x < UINT32_MAX; x++){
        clz1(x);
    }
    end1 = clock();

    start2 = clock();
    for( x = 0; x < UINT32_MAX; x++){
        clz2(x);
    }  
    end2 = clock();


    printf("clz1() : %lf sec\n", ((double) (end1 - start1)) / CLOCKS_PER_SEC);
    printf("clz2() : %lf sec\n", ((double) (end2 - start2)) / CLOCKS_PER_SEC);
    return 0;
}