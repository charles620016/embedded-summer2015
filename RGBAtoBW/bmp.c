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
    bmp->bitsPerPixel = B2U16(info,14); assert(bmp->bitsPerPixel==32);
    bmp->compression = B2U32(info,16);
    bmp->imageSize = B2U32(info,20);
    bmp->xPixelsPerM = B2U32(info,24);
    bmp->yPixelsPerM = B2U32(info,28);
    bmp->colorsUsed = B2U32(info,32);
    bmp->colorsImportant = B2U32(info,36);

    // Image data
    bmp->data = (uint32_t*) malloc( DataSize(bmp) );
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
    printf("Info size = %u \n", bmp->size);
    printf("Width = %u \n", bmp->width);
    printf("Height = %u \n", bmp->height);
    printf("BitsPerPixel = %u \n", bmp->bitsPerPixel);
    printf("Compression = %u \n", bmp->compression);
    printf("================\n");
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

    printf("Save the picture successfully!\n");
}

void rgbaToBw(BMP *bmp, int width, int height, long stride){
    int row, col;
    uint32_t pixel, r, g, b, a, bw;
    uint32_t *data = bmp->data;

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            pixel = data[col + row * stride / 4];
            a = (pixel >> 24) & 0xff;
            r = (pixel >> 16) & 0xff;
            g = (pixel >> 8) & 0xff;
            b = pixel & 0xff;
            bw = (uint32_t) (r * 0.299 + g * 0.587 + b * 0.114);
            data[col + row * stride / 4] = (a << 24) + (bw << 16) + (bw << 8) + (bw);
        }
    }
}

void rgbaToBw_v1(BMP *bmp, int width, int height, long stride){
    int row, col;
    uint32_t pixel, r, g, b, a, bw;
    uint32_t *data = bmp->data;

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            pixel = data[col + row * stride / 4];
            a = (pixel >> 24) & 0xff;
            r = (pixel >> 16) & 0xff;
            g = (pixel >> 8) & 0xff;
            b = pixel & 0xff;
            bw = (uint32_t) (table_R[r] + table_G[g] + table_B[b]);
            data[col + row * stride / 4] = (a << 24) + (bw << 16) + (bw << 8) + (bw);
        }
    }
}

void generateRGBTable(){
    int i;
    for(i = 0; i <= 0xff; i++){
        table_R[i] = i * 0.299;
        table_G[i] = i * 0.587;
        table_B[i] = i * 0.114;
    }
}

void rgbaToBw_v2(BMP *bmp, int width, int height, long stride){
    int row, col;
    uint32_t *pixel = bmp->data;
    BYTE *r, *g, *b, bw;

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            r = (BYTE *) pixel + 2;
            g = (BYTE *) pixel + 1;
            b = (BYTE *) pixel;
            bw = (*r * 0.299) + (*g * 0.587) + (*b * 0.114);
            *r = *g = *b = bw;
            pixel++;
        }
    }
}

void rgbaToBw_v3(BMP *bmp, int width, int height, long stride){
    int row, col;
    uint32_t *pixel = bmp->data;
    BYTE *r, *g, *b, bw;

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            r = (BYTE *) pixel + 2;
            g = (BYTE *) pixel + 1;
            b = (BYTE *) pixel;
            bw = table_R[*r] + table_G[*g] + table_B[*b];
            *r = *g = *b = bw;
            pixel++;
        }
    }
}

asm(
"   .global    rgbaToBw_v4             \n"
"   .type      rgbaToBw_v4, %function  \n"
"rgbaToBw_v4: \n"
"   @ args = 0, pretend = 0, frame = 8 \n"
"   @ frame_needed = 0, uses_anonymous_args = 0 \n"
"   cmp    r2, #0                      \n"
"   bxle   lr                          \n"
"   stmfd  sp!,{r4-r6,lr}              \n"
"   pld    [r0, #0]                    \n"
"   mov    r3, #77                     \n"
"   mov    r4, #151                    \n"
"   mov    r5, #28                     \n"
"   vdup.8 d0, r3                      \n"
"   vdup.8 d1, r4                      \n"
"   vdup.8 d2, r5                      \n"
"   mul    r3, r1, r2                  \n"
"   add    r4, r0, r3, lsl #2          \n"
"   mov    r3, r0                      \n"
".V4_LOOP:                             \n"
"   pld       [r0, #64]                \n"
"   @ (alpha,R,G,B) = (d7,d6,d5,d4)    \n"
"   vld4.8    {d4-d7}, [r0]!           \n"
"   vmull.u8    q10, d6, d0            \n"
"   vmlal.u8    q10, d5, d1            \n"
"   vmlal.u8    q10, d4, d2            \n"
"   vshrn.u16   d4, q10, #8            \n"
"   vmov   d5, d4                      \n"
"   vmov   d6, d4                      \n"
"   vst4.8    {d4-d7}, [r3]!           \n"
"   cmp        r0, r4                  \n"
"   blt    .V4_LOOP                    \n"
"   @ sp needed                        \n"
"   ldmfd    sp!, {r4-r6,pc}           \n"
"   .size    rgbaToBw_v4, .-rgbaToBw_v4 \n"
);

asm(
"   .global    rgbaToBw_v5             \n"
"   .type    rgbaToBw_v5, %function    \n"
"rgbaToBw_v5: \n"
"   @ args = 0, pretend = 0, frame = 8 \n"
"   @ frame_needed = 0, uses_anonymous_args = 0 \n"
"   cmp    r2, #0 \n"
"   bxle    lr \n"
"   stmfd    sp!,{r4-r6,lr}            \n"

"   pld    [r0, #0]                    \n"
"   pld    [r0, #64]                   \n"
"   mov    r3, #77                     \n"
"   mov    r4, #151                    \n"
"   mov    r5, #28                     \n"
"   vdup.8    d0, r3                   \n"
"   vdup.8    d1, r4                   \n"
"   vdup.8    d2, r5                   \n"

"   mul    r3, r1, r2                  \n"
"   add    r4, r0, r3, lsl #2          \n"
"   mov    r3, r0                      \n"

".V5_LOOP:                             \n"
"   pld    [r0, #128]                  \n"
"   pld    [r0, #192]                  \n"
"   vld4.8    {d4-d7}, [r0]!           \n"
"   vld4.8    {d8-d11}, [r0]!          \n"
"   vld4.8    {d12-d15}, [r0]!         \n"
"   vld4.8    {d16-d19}, [r0]!         \n"
"   vmull.u8    q10, d4, d2            \n"
"   vmull.u8    q11, d8, d2            \n"
"   vmull.u8    q12, d12, d2           \n"
"   vmull.u8    q13, d16, d2           \n"
"   vmlal.u8    q10, d5, d1            \n"
"   vmlal.u8    q11, d9, d1            \n"
"   vmlal.u8    q12, d13, d1           \n"
"   vmlal.u8    q13, d17, d1           \n"
"   vmlal.u8    q10, d6, d0            \n"
"   vmlal.u8    q11, d10, d0           \n"
"   vmlal.u8    q12, d14, d0           \n"
"   vmlal.u8    q13, d18, d0           \n"
"   vshrn.u16   d4, q10, #8            \n"
"   vshrn.u16   d8, q11, #8            \n"
"   vshrn.u16   d12, q12, #8           \n"
"   vshrn.u16   d16, q13, #8           \n"
"   vmov    d5, d4                     \n"
"   vmov    d6, d4                     \n"
"   vst4.8    {d4-d7}, [r3]!           \n"
"   vmov    d9, d8                     \n"
"   vmov    d10, d8                    \n"
"   vst4.8    {d8-d11}, [r3]!          \n"
"   vmov    d13, d12                   \n"
"   vmov    d14, d12                   \n"
"   vst4.8    {d12-d15}, [r3]!         \n"
"   vmov    d17, d16                   \n"
"   vmov    d18, d16                   \n"
"   vst4.8    {d16-d19}, [r3]!         \n"
"   cmp        r0, r4                  \n"
"   blt    .V5_LOOP                    \n"
"   @ sp needed                        \n"
"   ldmfd    sp!, {r4-r6,pc}           \n"
"   .size    rgbaToBw_v5, .-rgbaToBw_v5 \n"
);