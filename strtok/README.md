#### strtok()

C 語言的 strtok 函式作用為何？是否會有 reentrancy 議題？
若會，如何實做可避免 reentrancy 的版本？

```c
char *strtok(char *str, const char *delim);
```

若一開始不知道如何使用，可以 `$ man strtok` 了解定義、參數、回傳值。先看個簡單例子
```c
int main(){
   char str[80] = "Summer embedded (2015) - NCKU";
   const char delim[5] = " -()";
   char *token;
   
   /* get the first token */
   token = strtok(str, delim);
   
   /* walk through other tokens */
   while( token != NULL ) {
      printf( "%s\n", token );
      token = strtok(NULL, delim);
   }
   
   return 0;
}
```

比較有趣的地方就在於第一次呼叫是傳入愈分割的字串 str，但在 while 裡面卻是 NULL。打開 strtok.c 原始碼 ，可以發現有一個 static 的指標變數 olds 保存下一次分割的起始位置，若 s 傳入 NULL 則將 olds 拿來繼續分割。

不過很明顯的問題就是因為用了 static 變數後，若有多個 thread 同時叫用這個函式那這個變數 olds 就會混亂，如果寫的不小心，在同一個程式分割兩個字串也很容易出現錯誤。

若要使得strtok() thread-safe，那我們就讓使用者自己去宣告一個變數去保存下一次分割的起始位置。

修改後程式碼：strtok_reentrant.c