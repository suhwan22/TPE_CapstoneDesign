#ifndef UTILS_HPP
# define UTILS_HPP

#include "bmp.hpp"

/* init_bmp_header.cpp */
void    init_header(unsigned char *buffer, BMP_FileHeader *fileheader, BMP_InfoHeader *infoheader);

/* save_bmp_data.cpp */
void	save_bmp_data(BMP_File *img, unsigned char *bmp_data);

/* create_bmp.cpp */
int		create_bmp(BMP_File *image, char *file_name);
int		create_bmp_with_pixel_data(BMP_File *image, unsigned char *pixel, char *file_name);

/* recv_data_from_client.cpp */
unsigned char	*recv_data_from_client(int clntSock);

/* send_data_to_client.cpp */
void	send_data_to_client(int clntSock, unsigned char *pixel_data, unsigned int data_size);

unsigned char	*my_strjoin(unsigned char *str1, unsigned char *str2, unsigned int len1, unsigned int len2);

unsigned char	*my_strtrim(unsigned char *str, unsigned int len);

#endif
