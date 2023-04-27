#include "tpe.h"

int create_bmp(BMP_File *bmp_file, char *file_name)
{
	FILE *fp_bmp_output;

	if (fopen_s(&fp_bmp_output, file_name, "wb") != 0)
    {
        printf("Error: create_bmp\n");
        return (0);
    }
	fwrite(bmp_file->header, sizeof(unsigned char), 54, fp_bmp_output);
	unsigned char *tmp_byte_data;

	tmp_byte_data = malloc(sizeof(unsigned char) * bmp_file->img_size);
	for (int row = 0; row < bmp_file->bmp_infoheader.height; row++)
		for (int col = 0; col < bmp_file->bmp_infoheader.width; col++)
			for (int channel = 2; channel >= 0; channel--)
				tmp_byte_data[row * bmp_file->bmp_infoheader.width * 3 + col * 3 + channel] = bmp_file->pixel_data[row * bmp_file->bmp_infoheader.width * 3 + col * 3 + channel];
	fwrite(tmp_byte_data, sizeof(unsigned char), bmp_file->img_size, fp_bmp_output);
	fclose(fp_bmp_output);
    return (1);
}

int create_bmp_with_pixel_data(BMP_File *bmp_file, unsigned char *pixel, char *file_name)
{
	FILE *fp_bmp_output;

	if (fopen_s(&fp_bmp_output, file_name, "wb") != 0)
    {
        printf("Error: create_bmp\n");
        return (0);
    }
	printf("create_bmp()\nw: %d, h: %d, size: %d\n", bmp_file->bmp_infoheader.width, bmp_file->bmp_infoheader.height, bmp_file->img_size);
	fwrite(bmp_file->header, sizeof(unsigned char), 54, fp_bmp_output);
	unsigned char *tmp_byte_data;

	tmp_byte_data = malloc(sizeof(unsigned char) * bmp_file->img_size);
	for (int row = 0; row < bmp_file->bmp_infoheader.height; row++)
	{
		for (int col = 0; col < bmp_file->bmp_infoheader.width; col++)
			for (int channel = bmp_file->bits - 1; channel >= 0; channel--)
			{
				tmp_byte_data[row * bmp_file->bmp_infoheader.width * bmp_file->bits + col * bmp_file->bits + channel] = pixel[row * bmp_file->bmp_infoheader.width * bmp_file->bits + col * bmp_file->bits + channel];
			}
		//printf("row: %d\n", row);
	}
	fwrite(tmp_byte_data, sizeof(unsigned char), bmp_file->img_size, fp_bmp_output);
	fclose(fp_bmp_output);
	free(tmp_byte_data);
    return (1);
}