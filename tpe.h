#ifndef TPE_H
# define TPE_H

# define uint16_t unsigned short
# define uint32_t unsigned int
# define int32_t int

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
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

/* init_bmp_header.c */
void    init_header(unsigned char *buffer, BMP_FileHeader *fileheader, BMP_InfoHeader *infoheader);

/* save_bmp_file.c */
int save_bmp_file(BMP_File *img, char *file_name);

/* create_bmp.c */
int create_bmp(BMP_File *image, char *file_name);
int create_bmp_with_pixel_data(BMP_File *image, unsigned char *pixel, char *file_name);

/* substitution.c */
unsigned char *substitution(BMP_File bmp_file, unsigned char *image);

/* create_random_n_arr.c */
int *create_random_n_arr(int size);

/* permutation.c */
unsigned char *permutation(BMP_File bmp_file, unsigned char *image, int *random_arr, int block_size);

#endif