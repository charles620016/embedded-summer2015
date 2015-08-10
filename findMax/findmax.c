#include <stdio.h>
#include <stdint.h>
#include <limits.h>

// positive:1 ; negative:0
int sign(int32_t a){ 
    return 1 ^ ((a >> 31) & 0x1); 
}

// different sign:1 ; same sign:0
int diff(int32_t a, int32_t b){
    return sign(a) ^ sign(b);
}

// return the maximum if they have same sign
int max1(int32_t a, int32_t b) { 
    return a * sign(a - b) + b * (1^sign(a - b)); 
}

// return the positive if they have different sign
int max2(int32_t a, int32_t b){
    return a * sign(a) + b * sign(b);
}

int main()
{
        int32_t a = INT_MAX - 2;
        int32_t b = -20;
        int32_t max = max1(a, b)*(1^diff(a, b)) + max2(a, b)*diff(a, b);
        printf("a = %d , b = %d\n", a, b);
        printf("maximum number is %d\n", max);

        return 0;
}