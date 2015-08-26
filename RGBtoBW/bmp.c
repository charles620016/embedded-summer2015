#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "bmp.h"

void bmpLoad(BMP *bmp, const char *fileName) {
    FILE *file;
    BYTE header[14];
    BYTE info[40];

    if ((file = fopen(fileName, "rb") ) == NULL ) {
        fprintf(stderr, "Error: bmpLoad(), File open fail!\n");
        exit(EXIT_FAILURE);
    }

    fread(header, 1, HEADER_SIZE, file);
    fread(info, 1, INFO_SIZE, file);
    memcpy(bmp->header, header, HEADER_SIZE);
    memcpy(bmp->info, info, INFO_SIZE);

    // Header
    bmp->signature = B2U16(header,0); assert(bmp->signature == 0x4D42);
    bmp->fileSize = B2U32(header,2);
    bmp->dataOffset = B2U32(header,10);

    // InfoHeader
    bmp->size = B2U32(info,0); assert(bmp->size==40);
    bmp->width = B2U32(info,4);
    bmp->height = B2U32(info,8);
    bmp->planes = B2U16(info,12); assert(bmp->planes==1);
    bmp->bitsPerPixel = B2U16(info,14); assert(bmp->bitsPerPixel==24);
    bmp->compression = B2U32(info,16);
    bmp->imageSize = B2U32(info,20);
    bmp->xPixelsPerM = B2U32(info,24);
    bmp->yPixelsPerM = B2U32(info,28);
    bmp->colorsUsed = B2U32(info,32);
    bmp->colorsImportant = B2U32(info,36);

    // Image data
    bmp->data = (BYTE*) malloc( DataSize(bmp) );
    fseek(file, bmp->dataOffset, SEEK_SET);
    fread(bmp->data, 1, DataSize(bmp), file);
    fclose (file);
}

void bmpPrint(BMP *bmp) {
    printf("==== Header ====\n");
    printf("Signature = %04X\n", bmp->signature); // 0x4d42 = BM
    printf("FileSize = %u \n", bmp->fileSize);
    printf("DataOffset = %u \n", bmp->dataOffset);
    printf("==== Info ======\n");
    printf("size = %u \n", bmp->size);
    printf("Width = %u \n", bmp->width);
    printf("Height = %u \n", bmp->height);
    printf("BitsPerPixel = %u \n", bmp->bitsPerPixel);
    printf("Compression = %u \n", bmp->compression);
    printf("ImageSize = %u \n", bmp->imageSize);
}

void bmpSetPixel(BMP *bmp, int x, int y, BYTE R, BYTE G, BYTE B) {
    Pixel *pixel;
    int idx = y * bmp->width + x;
    pixel = (Pixel*) &bmp->data[idx * sizeof(Pixel)];
    pixel->R = R;
    pixel->G = G;
    pixel->B = B;
}

void bmpSave(BMP *bmp, const char *fileName) {
    FILE *file;

    if ((file = fopen(fileName, "wb") ) == NULL ) {
        fprintf(stderr, "Error: bmpSave(), File create fail!\n");
        exit(EXIT_FAILURE);
    }

    fwrite(bmp->header, 1, HEADER_SIZE, file);
    fwrite(bmp->info, 1, INFO_SIZE, file);
    fseek(file, bmp->dataOffset, SEEK_SET);
    fwrite(bmp->data, 1, DataSize(bmp), file);
    fclose(file);
}