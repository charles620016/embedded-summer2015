#define MAX_LAST_NAME_SIZE 16
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    __PHONE_BOOK_ENTRY *pNext;
} PhoneBook;

PhoneBook *FindName(char last[], PhoneBook *pHead) {
    while (pHead != NULL) {
        if (strcasecmp(last, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}