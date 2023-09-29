#ifndef UTILS_HPP
# define UTILS_HPP

#include "bmp.hpp"

/* create_random_n_arr.cpp */
int *create_random_n_arr(int size);

/* permutation.cpp */
unsigned char *permutation(BMP_File *bmp_file, unsigned char *image, int *random_arr, int block_size);

/* substitution.cpp */
unsigned char *substitution(BMP_File *bmp_file, unsigned char *image);

/* round.cpp */
unsigned char   *round_n(BMP_File *bmp_file, unsigned char *encry_img, int *random_arr, int block_size, int n);

/* init_bmp_header.cpp */
void    init_header(unsigned char *buffer, BMP_FileHeader *fileheader, BMP_InfoHeader *infoheader);

/* save_bmp_data.cpp */
void	save_bmp_data(BMP_File *img, unsigned char *bmp_data);

/* create_bmp.cpp */
int		create_bmp(BMP_File *image, char *file_name);
int		create_bmp_with_pixel_data(BMP_File *image, unsigned char *pixel, char *file_name);

/* recv_data_from_client.cpp */
char	*recv_data_from_client(int clntSock);

/* send_data_to_client.cpp */
void	send_data_to_client(int clntSock, unsigned char *pixel_data, unsigned int data_size);

char	*my_strjoin(char *str1, char *str2, unsigned int len1, unsigned int len2);

unsigned char	*my_strtrim(unsigned char *str, unsigned int len);

#endif
