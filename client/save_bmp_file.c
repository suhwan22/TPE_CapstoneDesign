#include "client.h"

int save_bmp_file(BMP_File *bmp_file, char *file_name)
{
    FILE*			fp_original;
	unsigned char	*icc_data;

	fp_original = fopen(file_name, "rb");
	if (!fp_original)
    {
		printf("Error: save_bmp_file(): bmp_file error\n");
        return (0);
    }
	fread(bmp_file->header, sizeof(unsigned char), 14, fp_original);
	init_header(bmp_file->header, &bmp_file->bmp_fileheader);

	fread(bmp_file->infoheader3, sizeof(unsigned char), 40, fp_original);
	init_infoheader3(bmp_file->infoheader3, &bmp_file->bmp_infoheader);

	if (bmp_file->bmp_infoheader.size == 40)
	//if BITMAPV3_HEADER
	{
		memset(&bmp_file->bmp_infoheader5, 0, 84);
	}
	else
	//if BITMAPV5_HEADER
	{
		fread(bmp_file->infoheader5, sizeof(unsigned char), 84, fp_original);
		init_infoheader5(bmp_file->infoheader5, &bmp_file->bmp_infoheader5);
	}

    bmp_file->bits = bmp_file->bmp_infoheader.bit_per_pixel / 8;
    bmp_file->img_size =  bmp_file->bits * bmp_file->bmp_infoheader.width * bmp_file->bmp_infoheader.height;
    bmp_file->pixel_data = malloc(sizeof(unsigned char) * bmp_file->img_size);
	if (!bmp_file->pixel_data)
	{
		printf("Error: save_bmp_file\n");
		return (0);
	}
    fread(bmp_file->pixel_data, sizeof(unsigned char), bmp_file->img_size, fp_original);

	if (bmp_file->bmp_infoheader5.ICC_profile_size != 0)
	{
		icc_data = (unsigned char *)malloc(sizeof(unsigned char) * bmp_file->bmp_infoheader5.ICC_profile_size);
		if (!icc_data)
		{
			printf("Error: save_bmp_file(): malloc()\n");
	        return (0);
		}
		fread(icc_data, sizeof(unsigned char), bmp_file->bmp_infoheader5.ICC_profile_size, fp_original);
		bmp_file->ICC_data = icc_data;
	}

	printf("headerSize: %d\n", bmp_file->bmp_infoheader.size);
	printf("filesize: %d\n", bmp_file->bmp_fileheader.size);
	printf("offset: %d\n", bmp_file->bmp_fileheader.offset);
	printf("colorUsed: %d\n", bmp_file->bmp_infoheader.colors_used);
	printf("ICC data: %d\n", bmp_file->bmp_infoheader5.ICC_profile_data);
	printf("ICC size: %d\n", bmp_file->bmp_infoheader5.ICC_profile_size);

    fclose(fp_original);
    return (1);
}
