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

void insert(PhoneBook *entries, char *lastName)
{
    /* Iterate through the list till we encounter the last entry.*/
    while(entries->pNext != NULL){
        entries = entries->pNext;
    }

    /* Allocate memory for the new entry and put lastName in it.*/
    entries->pNext = (PhoneBook *) malloc(sizeof(PhoneBook));
    entries = entries->pNext;
    strcpy(entries->lastName, lastName);
    entries->pNext = NULL;
}