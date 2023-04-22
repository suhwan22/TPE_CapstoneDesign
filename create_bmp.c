#include "tpe.h"

int create_bmp(BMP_Image *image, char *file_name)
{
	FILE *fp_bmp_output;

	if (fopen_s(&fp_bmp_output, file_name, "wb") != 0)
    {
        printf("Error: create_bmp\n");
        return (0);
    }
	fwrite(image->header, sizeof(unsigned char), 54, fp_bmp_output);
	unsigned char *tmp_byte_data;

	tmp_byte_data = malloc(sizeof(unsigned char) * image->img_size);
	for (int row = 0; row < image->bmp_infoheader.height; row++)
		for (int col = 0; col < image->bmp_infoheader.width; col++)
			for (int channel = 2; channel >= 0; channel--)
				tmp_byte_data[row * image->bmp_infoheader.width * 3 + col * 3 + channel] = image->pixel_data[row * image->bmp_infoheader.width * 3 + col * 3 + channel];
	fwrite(tmp_byte_data, sizeof(unsigned char), image->img_size, fp_bmp_output);
	fclose(fp_bmp_output);
    return (1);
}

int create_bmp_with_pixel_data(BMP_Image *image, unsigned char *pixel, char *file_name)
{
	FILE *fp_bmp_output;

	if (fopen_s(&fp_bmp_output, file_name, "wb") != 0)
    {
        printf("Error: create_bmp\n");
        return (0);
    }
	fwrite(image->header, sizeof(unsigned char), 54, fp_bmp_output);
	unsigned char *tmp_byte_data;

	tmp_byte_data = malloc(sizeof(unsigned char) * image->img_size);
	for (int row = 0; row < image->bmp_infoheader.height; row++)
		for (int col = 0; col < image->bmp_infoheader.width; col++)
			for (int channel = 2; channel >= 0; channel--)
				tmp_byte_data[row * image->bmp_infoheader.width * 3 + col * 3 + channel] = pixel[row * image->bmp_infoheader.width * 3 + col * 3 + channel];
	fwrite(tmp_byte_data, sizeof(unsigned char), image->img_size, fp_bmp_output);
	fclose(fp_bmp_output);
    return (1);
}