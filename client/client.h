#ifndef CLIENT_H
# define CLIENT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <math.h>

typedef struct BMP_FileHeader
{
    uint16_t	type;
    uint32_t	size;
    uint16_t	reserved1;
    uint16_t	reserved2;
    uint32_t	offset;
}   BMP_FileHeader;

typedef struct BMP_InfoHeaderV3
{
    uint32_t	size;
    int32_t		width;
    int32_t 	height;
    uint16_t	planes;
    uint16_t	bit_per_pixel;
    uint32_t	compression;
    uint32_t	size_image;
    int32_t		x_pixels_per_meter;
    int32_t		y_pixels_per_meter;
    uint32_t	colors_used;
    uint32_t	colors_important;
}   BMP_InfoHeader;

typedef struct BMP_InfoHeaderV5
{
	uint32_t		red_channel_mask;
	uint32_t		green_channel_mask;
	uint32_t		blue_channel_mask;
	uint32_t		alpha_channel_mask;
	uint32_t		color_space_type;
	unsigned char	color_space_endpoint[36];
	uint32_t		gamma_red_channel;
	uint32_t		gamma_green_channel;
	uint32_t		gamma_blue_channel;
	uint32_t		intent;
	uint32_t		ICC_profile_data;
	uint32_t		ICC_profile_size;
	uint32_t		reserved;
}   BMP_InfoHeader5;

typedef struct BMP_File
{
    unsigned char		header[14];
	unsigned char		infoheader3[40];
	unsigned char		infoheader5[52];
	unsigned char		*others;
	unsigned char		*ICC_data;
    BMP_FileHeader		bmp_fileheader;
    BMP_InfoHeader		bmp_infoheader;
    BMP_InfoHeader5		bmp_infoheader5;
    unsigned char		*pixel_data;
    unsigned int		bits;
    unsigned int		img_size;
}   BMP_File;

/* init_bmp_header.c */
void    init_header(unsigned char *buffer, BMP_FileHeader *fileheader);
void	init_infoheader3(unsigned char *buffer, BMP_InfoHeader *infoheader);
void	init_infoheader5(unsigned char *buffer, BMP_InfoHeader5 *infoheader);

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
void	send_data_to_server(int servSock, BMP_File *bmp_data);

/* utils.c */
unsigned char	*my_join(unsigned char *str1, unsigned char *str2, unsigned int len1, unsigned int len2);

/* block.c */
unsigned char *getNthBlock(BMP_File *bmp_file, int n, int block_size, unsigned int *return_size);
#endif
