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