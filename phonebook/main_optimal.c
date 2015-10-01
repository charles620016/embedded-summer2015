#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "phonebook.h"

#define INPUT_SIZE 8

int main(int argc, char const *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    clock_t start, end;
    double cpuTimeUsed1, cpuTimeUsed2;

    /* check file opening*/     
    fp = fopen("./dictionary/words.txt", "r");
    if (fp == NULL){
        printf("cannot open the file\n");
        return 0;
    }

    /* build the last name entry */
    lastNameEntry *pHead, *lne;
    pHead = (lastNameEntry *) malloc(sizeof(lastNameEntry));
    printf("size of entry : %lu bytes\n", sizeof(lastNameEntry));
    lne = pHead;
    lne->pNext = NULL;
    start = clock();
    while (fgets(line, sizeof(line), fp)){
        while(line[i] != '\0'){
            i++;
        }
        line[i-1] = '\0';
        i = 0;
        lne = appendOptimal(line, lne);
    }
    end = clock();
    cpuTimeUsed1 = ((double) (end - start)) / CLOCKS_PER_SEC;

    /* input lastName */
    char input[INPUT_SIZE][MAX_LAST_NAME_SIZE] = {"uninvolved","zyxel","whiteshank", 
                "odontomous", "pungoteague", "reweighted", "xiphisternal", "yakattalo"};

    /* compute the execution time */
    lne = pHead;
    int j;
    start = clock();
    for(j = 0; j < INPUT_SIZE; j++){
        findNameOptimal(input[j], lne);
        lne = pHead;
    }
    end = clock();
    cpuTimeUsed2 = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("execution time of appendOptimal() : %lf\n", cpuTimeUsed1);
    printf("execution time of findNameOptimal() : %lf\n", cpuTimeUsed2);

    /* release the resource */
    free(pHead);
    fclose(fp);

    return 0;
}