#include "tpe.h"

int save_bmp_file(BMP_File *bmp_file, char *file_name)
{
    FILE* fp_lenna_original;

	fp_lenna_original = fopen(file_name, "rb");
	if (!fp_lenna_original)
    {
		printf("Error: save_bmp_file(): bmp_file error\n");
        return (0);
    }
	fread(bmp_file->header, sizeof(unsigned char), 54, fp_lenna_original);
	init_header(bmp_file->header, &bmp_file->bmp_fileheader, &bmp_file->bmp_infoheader);
    bmp_file->bits = bmp_file->bmp_infoheader.bit_count / 8;
    bmp_file->img_size =  bmp_file->bits * bmp_file->bmp_infoheader.width * bmp_file->bmp_infoheader.height;
    bmp_file->pixel_data = malloc(sizeof(unsigned char) * bmp_file->img_size);
	if (!bmp_file->pixel_data)
	{
		printf("Error: save_bmp_file\n");
		return (0);
	}
    fread(bmp_file->pixel_data, sizeof(unsigned char), bmp_file->img_size, fp_lenna_original);
    fclose(fp_lenna_original);
    return (1);
}
