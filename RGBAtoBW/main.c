#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bmp.h"

int main(int argc, char *argv[]) {
    char openfile[] = "./pictures/01.bmp";
    char savefile[] = "./pictures/01_after.bmp";
    BMP *bmp = (BMP*) malloc(sizeof(BMP));
    clock_t start = 0;
    clock_t end = 0;

    bmpLoad(bmp, openfile);
    bmpPrint(bmp);

    /* RGBA to BW */
    printf("RGBA to BW is in progress....\n");
    #if defined(ORIGIN)
        printf("Original version\n");
        start = clock();
        rgbaToBw(bmp, bmp->width, bmp->height, 5120);
        end = clock();
    #endif

    #if defined(VERSION1)
        printf("Version 1 : using RGB table\n");
        generateRGBTable();
        start = clock();
        rgbaToBw_v1(bmp, bmp->width, bmp->height, 5120);
        end = clock();
    #endif

    bmpSave(bmp, savefile);
    printf("Execution time of rgbaToBw() : %lf \n", ((double) (end - start)) / CLOCKS_PER_SEC);

    return 0;
}