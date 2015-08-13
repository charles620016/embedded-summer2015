#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"

PhoneBook *findName(char last[], PhoneBook *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(last, pHead->lastName) == 0){
            printf("%s\n", "found it!");
            return pHead;
        }
        pHead = pHead->pNext;
    }
    printf("%s\n", "not found");
    return NULL;
}

PhoneBook *append(char *lastName, PhoneBook *entry)
{
    /* Allocate memory for the new entry and put lastName in it.*/
    entry->pNext = (PhoneBook *) malloc(sizeof(PhoneBook));
    entry = entry->pNext;
    strcpy(entry->lastName, lastName);
    entry->pNext = NULL;

    return entry;
}