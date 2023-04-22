#include "tpe.h"

int save_bmp_file(BMP_Image *img, char *file_name)
{
    FILE* fp_lenna_original;

	if (fopen_s(&fp_lenna_original, file_name, "rb") != 0)
        return (0);
	fread(img->header, sizeof(unsigned char), 54, fp_lenna_original);
	init_header(img->header, &img->bmp_fileheader, &img->bmp_infoheader);
    img->img_size = 3 * img->bmp_infoheader.width * img->bmp_infoheader.height;
    img->pixel_data = malloc(sizeof(unsigned char) * img->img_size);
    fread(img->pixel_data, sizeof(unsigned char), img->img_size, fp_lenna_original);
    fclose(fp_lenna_original);
    return (1);
}