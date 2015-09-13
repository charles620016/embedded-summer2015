###*Phonebook*

下面是一個電話簿的姓名查找程式，使用linked list實作。

```c
    #define MAX_LAST_NAME_SIZE 16
    typedef struct __PHONE_BOOK_ENTRY {
        char LastName[MAX_LAST_NAME_SIZE];
        char FirstName[16];
        char email[16];
        char phone[10];
        char cell[10];
        char addr1[16];
        char addr2[16];
        char city[16];
        char state[2];
        char zip[5];
        struct __PHONE_BOOK_ENTRY *pNext;
    } PhoneBook;

    PhoneBook *FindName(char Last[], PhoneBook *pHead) {
        while (pHead != NULL) {
            if (stricmp(Last, pHead->LastName) == 0)
                return pHead;
            pHead = pHead->pNext;
        }
        return NULL;
    }
```
它存在一些效能的問題，要如何優化程式碼？如何設計良好的benchmark？

hint：cache miss
hint：hash function

---

###*Implementation*
[詳情筆記參考：Week 2 課後作業](https://embedded2015.hackpad.com/Charles-2015--7sVmkgm4Hre#:h=課後作業---phonebook)

`＄lscpu | grep cache ` 來得知電腦 L1 ～ Last-level cache 大小
```
L1d cache:             32K
L1i cache:             32K
L2 cache:              256K
L3 cache:              3072K
```

一開始想先使用 profiling tool 了解未優化前程式 cache hit / miss 的情形。

perf 是 Linux kernel 內建的系統性能優化工具，它比OProfile, GProf 的優勢在於與 Linux Kernel 緊密結合，它可以最先應用到加入 Kernel 的 new feature。perf 基本原理是對目標進行取樣，例如根據 tick 中斷進行取樣，即在 tick 中斷內觸發取樣點，在取樣點裡判斷行程當時的上下文。假如一個行程 90% 的時間都花費在函式 foo() 上，那麼 90% 的取樣點都應該落在函式 foo() 的上下文中。

*  檢測 cache miss event 前需要取消 kernel pointer 的禁用
`$ sudo sh -c " echo 0 > /proc/sys/kernel/kptr_restrict" `

*  檢測程式執行期間有多少次 cache miss 指令
`$ perf stat -e cache-misses ./main`

*  查看觸發 cache miss 的函式
`$ perf record -e cache-misses ./main`
`$ perf report`

<br />
####第一種優化方式：使用體積較小的 struct。

```c
typedef struct __LAST_NAME_ENTRY{
    char lastName[MAX_LAST_NAME_SIZE];
    entry *detail;
    struct __LAST_NAME_ENTRY *pNext;
} lastNameEntry;
```

希望能不改變原本 phonebook entry 的結構，所以我另外設計一個 struct 只儲存 last name，並用一個指向phonebook entry 的指標叫 *detail 來儲存詳細資訊，新的 struct 大小只有 32 bit，這樣搜尋的過程中，cache 就可以塞進更多資料，增加 cache hit 的機率。

另外我實作 appendOptimal() 中，*detail 並沒有沒指向一塊空間，我想專心讓 appendOptimal() 產生含有 lastName 的節點就好。為什麼呢？因為若在 append 過程中 malloc() 空間給 *detail，會增加很多 cache miss，嚴重影響到效能表現，經過實測，總體效能甚至比原始版本還差一點。目前想法是將 *detail 的 assign （當有需要時）交給另外一個 function 處理，畢竟我們一開始只有 last name 的資訊。 

<br />

####第二種優化方式：使用 hash function。

利用字串當作key，對 hash table 作搜尋顯然比每次從頭開始查找快多了。為了只更動一個變因，hash table 裡的 entry 仍按照原來題目給的，「不是」瘦身過後的 entry。所以接下來的問題就是，如何選擇 hash function？如何減少碰撞發生呢？我選了兩種 hash function。不過以下先用 hash2() 和上面的結果作比較。另外 table size 我使用 42737，挑選的原因是因為有約35萬個英文單字，為了減少碰撞機會，挑了一了蠻大的「質數」。

<br />

####討論與分析:

***執行時間***

*  findName()：查找 last name 的時間上，兩種優化版本的顯然都比原始的還要好，甚至 hash 版本的時間比原始快了近30倍。可見有了 hash table ，不用每次從 35萬個單字的頭開始找起，省掉許多時間。

*  append()：建立 hash table 比起建立optimal版的 linked list 慢了一些， 主要是因為還多了計算 hash function 這個步驟，不過並沒有慢很多，差 2～3 ms。
![](https://raw.githubusercontent.com/charles620016/embedded-summer2015/master/phonebook/screenshot/01.png)

***cache miss 情形***

perf stat 效能分析的結果是總和的 cache miss event，所以除了findName()，也包含 append() 過程中產生的 cache miss。這次結果是 optimal 版本的 cache miss 次數只有 origin 版本的 1 / 4，佔所有 cache references 的比例也有下降約 21％，果然在修改 struct 大小後有非常大的改善。

<p align="center">
<img src="https://raw.githubusercontent.com/charles620016/embedded-summer2015/master/phonebook/screenshot/02.jpg" >
</p>

至於 hash 版本的 cache miss 似乎沒有 optimal 表現來得優異，我認為主要是因為我前面有提到「為了只更動一個變因，hash table 裡的 entry 仍按照原來題目給的，『不是』瘦身過後的 entry」，也就是說，hash 版本的 append 仍跟原始版本一樣，要 malloc() 136 bit 這麼大的記憶體空間，findName() 過程中也要在 cache 中存 136 bit 大小的 entry，即使不用查找那麼多次就可以中，但仍會有些 cache miss 。所以如果要針對 hash 版本繼續優化，那麼可以結合 optimal 版本，縮小 struct 大小。 
