###*設計一個演算法，找出兩個數裡面較大的數 ( 不得使用 if-else 或 < > 一類比較的運算子 )*

先將範圍限縮在32位元有號整數。

Hint 1 : (a - b) 的正負號，搭配乘法。

Hint 2 :
```c
// a 為正數則返回 1，a 為負數則返回 0
int sign(int32_t a){ return 1 ^ ((a >> 31) & 0x1); }

// 回傳a , b最大值
int max(int32_t a, int32_t b){ return a * sign(a - b) + b * (1 ^ sign(a - b)); }
```

問題：若 a = INT_MAX(整數的上界) - 2, b = -15 則會遇到 integer overflow，請改出避免 integer overflow 的實做。

-----

###*Implementation*
當 integer overflow 發生時，a , b 必定異號，而正整數的那個就是max。
同號時使用上面的max()，異號時使用另外一種 max()，再使用 XOR 來選擇。

```c
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
```
