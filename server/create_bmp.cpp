#include <iostream>
#include <cstdlib>
#include "utils.hpp"

int create_bmp(BMP_File *bmp_file, char *file_name)
{
	FILE *fp_bmp_output;

	fp_bmp_output = fopen(file_name, "wb");
	if (!fp_bmp_output)
    {
		std::cout << "Error: create_bmp" << std::endl;
        return (0);
    }

	fwrite(bmp_file->header, sizeof(unsigned char), 54, fp_bmp_output);
	unsigned char *tmp_byte_data;

	tmp_byte_data = (unsigned char *)malloc(sizeof(unsigned char) * bmp_file->img_size);
	if (!tmp_byte_data)
	{
		std::cout << "Error: create_bmp: tmp_byte_data malloc error" << std::endl;
		return (0);
	}

	for (int row = 0; row < bmp_file->bmp_infoheader.height; row++)
		for (int col = 0; col < bmp_file->bmp_infoheader.width; col++)
			for (int channel = 2; channel >= 0; channel--)
			{
				tmp_byte_data[row * bmp_file->bmp_infoheader.width * 3 + col * 3 + channel] \
					= bmp_file->pixel_data[row * bmp_file->bmp_infoheader.width * 3 + col * 3 + channel];
			}
	fwrite(tmp_byte_data, sizeof(unsigned char), bmp_file->img_size, fp_bmp_output);
	fclose(fp_bmp_output);
    return (1);
}

int create_bmp_with_pixel_data(BMP_File *bmp_file, unsigned char *pixel, char *file_name)
{
	FILE *fp_bmp_output;

	fp_bmp_output = fopen(file_name, "wb");
	if (!fp_bmp_output)	
	{
		std::cout << "Error: create_bmp" << std::endl;
        return (0);
    }
	std::cout << "create_bmp()\nw: " << bmp_file->bmp_infoheader.width \
				<< ", h: " << bmp_file->bmp_infoheader.height \
				<< ", size: " << bmp_file->img_size << std::endl;
	fwrite(bmp_file->header, sizeof(unsigned char), 54, fp_bmp_output);
	unsigned char *tmp_byte_data;

	tmp_byte_data = (unsigned char *)malloc(sizeof(unsigned char) * bmp_file->img_size);
	if (!tmp_byte_data)
	{
		std::cout << "Error: create_bmp_with_pixel_data: tmp_byte_data malloc error" << std::endl;
		return (0);
	}

	for (int row = 0; row < bmp_file->bmp_infoheader.height; row++)
	{
		for (int col = 0; col < bmp_file->bmp_infoheader.width; col++)
			for (int channel = bmp_file->bits - 1; channel >= 0; channel--)
			{
				tmp_byte_data[row * bmp_file->bmp_infoheader.width * bmp_file->bits + col * bmp_file->bits + channel] \
					= pixel[row * bmp_file->bmp_infoheader.width * bmp_file->bits + col * bmp_file->bits + channel];
			}
	}
	fwrite(tmp_byte_data, sizeof(unsigned char), bmp_file->img_size, fp_bmp_output);
	fclose(fp_bmp_output);
	free(tmp_byte_data);
    return (1);
}
