#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook.h"

/* original version */
entry *findName(char lastname[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0){
            printf("%s\n", "found it!");
            return pHead;
        }
        pHead = pHead->pNext;
    }
    printf("%s\n", "not found");
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName in it.*/
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}


/* optimal version 1 */
lastNameEntry *findNameOpt(char lastName[], lastNameEntry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0){
            printf("%s\n", "found it!");
            return pHead;
        }
        pHead = pHead->pNext;
    }
    printf("%s\n", "not found");
    return NULL;
}

lastNameEntry *appendOpt(char lastName[], lastNameEntry *lne)
{
    /* allocate memory for the new entry and put lastName in it.*/
    lne->pNext = (lastNameEntry *) malloc(sizeof(lastNameEntry));
    lne = lne->pNext;
    strcpy(lne->lastName, lastName);
    lne->pNext = NULL;

    /* point to the detail information*/
    lne->detail = (entry *) malloc(sizeof(entry));
    strcpy(lne->detail->lastName, lastName);
    return lne;
}


/* optimal version 2 */
hashTable *createHashTable(int tableSize)
{
    hashTable *ht = NULL;
    int i;

    if( tableSize < 1 ){
        return NULL;
    }

    /* Allocate the table itself. */
    if((ht = (hashTable *) malloc(sizeof(hashTable))) == NULL) {
        return NULL;
    }

    /* Allocate array of list. */
    if( (ht->list = (entry **) malloc(sizeof(entry *)*tableSize)) == NULL ) {
        return NULL;
    }

    /* Allocate list header */
    for( i = 0; i < tableSize; i++ ) {
        ht->list[i] = NULL;
    }

    ht->tableSize = tableSize;

    return ht;
}

entry* findNameHash(char *key, hashTable *ht)
{
    entry *e;
    hashIndex index = hash3(key, ht);
    for(e = ht->list[index]; e != NULL; e = e->pNext){
        if ( strcasecmp(key, e->lastName) == 0 ){
            printf("%s\n", "found it!");
            return e;
        }
    }
    printf("%s\n", "not found");
    return NULL;
}

int appendHash(char *key, hashTable *ht)
{
    hashIndex index = hash3(key, ht);
    entry *newEntry;
    // entry *currentEntry;

    /* Does entry already exist? If it does, don't append it again. 
    if( (currentEntry = findNameHash(key, ht)) != NULL ){
        return 1;
    }*/

    /* attempt to allocate memory for entry */
    if ((newEntry = (entry *) malloc(sizeof(entry))) == NULL){
        return 2;
    }

    /* Insert into list */
    strcpy(newEntry->lastName, key);
    newEntry->pNext = ht->list[index];
    ht->list[index] = newEntry;

    return 0;
}

hashIndex hash2(char *key, hashTable *ht)
{   
    unsigned int hashVal = 0;
    while(*key != '\0'){
        hashVal+= *key++;
    }

    return hashVal % ht->tableSize;
}

hashIndex hash3(char *key, hashTable *ht)
{
    unsigned int hashVal = 0;
    while(*key != '\0'){
        hashVal = (hashVal << 5) + *key++;
    }

    return hashVal % ht->tableSize;
}
