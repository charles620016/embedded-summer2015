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

[Phone book 效能分析與討論](https://charles620016.hackpad.com/Linux-Perf-lifHi7P9FAL)