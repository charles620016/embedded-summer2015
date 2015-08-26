#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bmp.h"

int main(int argc, char *argv[]) {
    char openfile[] = "./pictures/01.bmp";
    char savefile[] = "./pictures/01_after.bmp";
    BMP *bmp = (BMP*) malloc(sizeof(BMP));
    clock_t start, end;

    bmpLoad(bmp, openfile);
    bmpPrint(bmp);

    /* RGB to BW */
    printf("RGBA to BW is in progress....\n");
    start = clock();
    rgbaToBw(bmp, bmp->width, bmp->height, 5120);
    end = clock();

    bmpSave(bmp, savefile);
    printf("Execution time of rgbaToBw() : %lf \n", ((double) (end - start)) / CLOCKS_PER_SEC);

    return 0;
}