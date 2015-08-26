#include <stdint.h>

#define HEADER_SIZE 14
#define INFO_SIZE 40
#define DataSize(bmp) ((bmp->width)*(bmp->height)*4)

#define U16(x)  ((unsigned short) (x))
#define U32(x)  ((int) (x))
#define B2U16(bytes,offset)  (U16(bytes[offset]) | U16(bytes[offset+1]) << 8)
#define B2U32(bytes,offset)  (U32(bytes[offset]) | U32(bytes[offset+1]) << 8 | U32(bytes[offset+2]) << 16 | U32(bytes[offset+3]) << 24)
                   
typedef unsigned char BYTE;

/* BMP file format Field */
typedef struct BMP {
    BYTE header[HEADER_SIZE];    
    BYTE info[INFO_SIZE];

    // Header 
    uint16_t signature; // Magic Number = "BM" = 0x4D42
    uint32_t fileSize; // File size in bytes
    uint32_t hreserved; // unused (=0)
    uint32_t dataOffset; // File offset to Raster Data

    // InfoHeader
    uint32_t size; // Size of InfoHeader =40 
    uint32_t width; // Bitmap Width
    uint16_t height; // Bitmap Height
    uint16_t planes; // Number of Planes (=1)
    uint16_t bitsPerPixel; // Bits per Pixel, 1, 4, 8, 16, 24, 32
    uint32_t compression; // Type of Compression, 0 = BI_RGB no compression, 1 = BI_RLE8 8bit RLE encoding, 2 = BI_RLE4 4bit RLE encoding
    uint32_t imageSize; // (compressed) Size of Image, It is valid to set this =0 if Compression = 0
    uint32_t xPixelsPerM; // horizontal resolution: Pixels/meter
    uint32_t yPixelsPerM; // vertical resolution: Pixels/meter
    uint32_t colorsUsed; // Number of actually used colors
    uint32_t colorsImportant; // Number of important colors , 0 = all

    // ColorTable : present only if Info.BitsPerPixel <= 8 colors should be ordered by importance
    BYTE blue; // Blue intensity
    BYTE green; // Green intensity
    BYTE red; // Red intensity
    BYTE creserved; // unused (=0)
    
    // Raster Data
    uint32_t *data;
} BMP;

typedef struct Pixel {
    BYTE A;
    BYTE R;
    BYTE G;
    BYTE B;
} Pixel;

/* function of bmp processing */
void bmpLoad(BMP *bmp, const char *fileName);
void bmpPrint(BMP *bmp);
void rgbaToBw(BMP *bmp, int width, int height, long stride);
void bmpSave(BMP *bmp, const char *fileName);
