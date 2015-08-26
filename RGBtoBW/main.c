#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "bmp.h"

int main(int argc, char *argv[]) {
    BMP bmp;
    char openfile[] = "./pictures/01.bmp";
    char savefile[] = "./pictures/01_after.bmp";

    bmpLoad(&bmp, openfile);
    bmpPrint(&bmp);
    bmpSave(&bmp, savefile);
    return 0;
}