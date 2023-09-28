#ifndef CLIENT_H
# define CLIENT_H

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

/* connect_server.c */
int	connect_server(char *ip, int port);

/* recv_data_from_server.c */
unsigned char	*recv_data_from_server(int servSock);

/* send_data_to_server.c */
void	send_data_to_server(int servSock, unsigned char *pixel_data, unsigned int data_size);

/* utils.c */
unsigned char	*my_strjoin(unsigned char *str1, unsigned char *str2, unsigned int len1, unsigned int len2);

#endif
