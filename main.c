#include "tpe.h"

int main(int argc, char **argv)
{
	BMP_File	origin_image;

	//if (argc != 3)
	//{
	//	printf("Error: need three args\n");
	// 	return (-1);
	//}
	if (!save_bmp_file(&origin_image, ".\\lenna_original.bmp"))
		return (-1);
    printf("width: %d, height: %d\n", origin_image.bmp_infoheader.width, origin_image.bmp_infoheader.height);

	unsigned char	*tpe_image;
	int				*random_arr;
	int				block_size;

	block_size = 16;
	random_arr = create_random_n_arr(block_size * block_size);
	tpe_image = origin_image.pixel_data;

	tpe_image = round_n(&origin_image, tpe_image, random_arr, block_size, 100);
	tpe_image = inverse_round_n(&origin_image, tpe_image, random_arr, block_size, 100);

	if (!tpe_image)
		return (-1);
	if (!create_bmp_with_pixel_data(&origin_image, tpe_image, ".\\test_image_1_1.bmp"))
		return (-1);
	//create_bmp_with_pixel_data(&origin_image, tpe_image, argv[2]);
	free(tpe_image);
    return 0;
}