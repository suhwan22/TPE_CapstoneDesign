#ifndef BMP_HPP
# define BMP_HPP

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <ctime>
# include <math.h>

typedef struct BMP_FileHeader
{
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
}   BMP_FileHeader;

typedef struct BMP_InfoHeader
{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t size_image;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
}   BMP_InfoHeader;

typedef struct BMP_File
{
    unsigned char   header[54];
    BMP_FileHeader  bmp_fileheader;
    BMP_InfoHeader  bmp_infoheader;
    unsigned char   *pixel_data;
    unsigned int    bits;
    unsigned int    img_size;
}   BMP_File;

#endif
