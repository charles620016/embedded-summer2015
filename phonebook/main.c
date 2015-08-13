#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"

int main(int argc, char const *argv[])
{
    FILE *fp;
    char line[MAX_LAST_NAME_SIZE];

    /* check file opening*/     
    fp = fopen("./dictionary/all-names.txt", "r");
    if (fp == NULL){
        printf("cannot open the file\n");
        return 0;
    }

    /* build the phonebook */
    int i = 0;
    PhoneBook *pHead, *entry;
    pHead = (PhoneBook *) malloc(sizeof(PhoneBook));
    entry = pHead;
    entry->pNext = NULL;
    while (fgets(line, sizeof(line), fp)){
        /* first, cut non-alphanumeric characters */    
        while (((line[i]>='a'&&line[i]<='z') || (line[i]>='A'&&line[i]<='Z'))){
            i++;
        }
        line[i]='\0';
        i = 0;
        entry = append(line, entry);
    }

    /* print the phonebook  
    entry = pHead;
    while(entry != NULL){
        printf("%s\n", entry->lastName);
        entry = entry->pNext;
    }*/

    /* find that whether the input lastName exists or not */
    char input[MAX_LAST_NAME_SIZE] = "zoe";
    printf("the last name which want to find out : %s\nresult : ", input);
    entry = pHead;
    findName(input, entry);
    fclose(fp);

    return 0;
}