#include "utils.hpp"
#include <iostream>

void	save_bmp_data(BMP_File *bmp_file, unsigned char *bmp_data)
{
	int i;

	for (i = 0; i < 54; i++)
		bmp_file->header[i] = bmp_data[i];
	init_header(bmp_file->header, &bmp_file->bmp_fileheader, &bmp_file->bmp_infoheader);
    bmp_file->bits = bmp_file->bmp_infoheader.bit_count / 8;
    bmp_file->img_size =  bmp_file->bits * bmp_file->bmp_infoheader.width * bmp_file->bmp_infoheader.height;
	std::cout << "bmp_file->bits : " << bmp_file->bits
		<< " bmp_file->bmp_infoheader.width : " << bmp_file->bmp_infoheader.width
		<< " bmp_file->bmp_infoheader.height : " << bmp_file->bmp_infoheader.height << std::endl;
	std::cout << "img_size : " << bmp_file->img_size << std::endl;
    bmp_file->pixel_data = (unsigned char *)malloc(sizeof(unsigned char) * bmp_file->img_size);
	if (!bmp_file->pixel_data)
	{
		std::cout << "Error: save_bmp_file" << std::endl;
		exit(1);
	}
	for (;i < bmp_file->img_size; i++)
		bmp_file->pixel_data[i] = bmp_data[i];
}
