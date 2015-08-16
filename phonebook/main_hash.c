#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "phonebook.h"

int main(int argc, char const *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    clock_t start, end;
    double cpuTimeUsed;

    /* check file opening*/     
    fp = fopen("./dictionary/all-names.txt", "r");
    if (fp == NULL){
        printf("cannot open the file\n");
        return 0;
    }

    /* create hash table. table size is a prime number*/
    int tableSize =  9973;
    hashTable *ht = createHashTable(tableSize);
    printf("hash table size (prime number) : %d\n", tableSize);

    /* build the entry */
    entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bits\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;
    while (fgets(line, sizeof(line), fp)){
        while(line[i] != '\0'){
            i++;
        }
        line[i-1] = '\0';
        i = 0;
        appendHash(line, ht);
    }

    /* find that whether the input lastName exists or not */
    char input[MAX_LAST_NAME_SIZE] = "zoe";
    printf("the last name which want to find out : %s\nresult : ", input);
    e = pHead;
    /* compute the execution time */
    start = clock();
    findNameHash(input, ht);
    end = clock();
    cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("execution time of findNameHash() : %lf\n", cpuTimeUsed);

    free(pHead);
    fclose(fp);

    return 0;
}