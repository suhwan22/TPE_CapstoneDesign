#include "tpe.h"

int main(int argc, char **argv)
{
	//save original bmp file
	BMP_File	origin_image;

	//if (argc != 3)
	//{
	//	printf("Error: need three args\n");
	// 	return (-1);
	//}
	//if (!save_bmp_file(&origin_image, "C:\\Users\\user\\source\\repos\\TPE_test\\cycle.bmp"))
	//if (!save_bmp_file(&origin_image, "C:\\Users\\user\\source\\repos\\TPE_test\\sushi_image\\sushi.bmp"))
	if (!save_bmp_file(&origin_image, ".\\lenna_image\\lenna_original.bmp"))
	//if (!save_bmp_file(&origin_image, argv[1]))
		return (-1);
    printf("width: %d, height: %d\n", origin_image.bmp_infoheader.width, origin_image.bmp_infoheader.height);

	unsigned char	*tpe_image;
	int				*random_arr;
	int				block_size;

	tpe_image = substitution(origin_image, origin_image.pixel_data);
	if (!tpe_image)
	 	return (-1);
	block_size = 4;
	random_arr = create_random_n_arr(block_size * block_size);
	tpe_image = permutation(origin_image, origin_image.pixel_data, random_arr, block_size);
	//create_bmp_with_pixel_data(&origin_image, tpe_image, "C:\\Users\\user\\source\\repos\\TPE_test\\sushi_image\\sushi_copy.bmp");
	create_bmp_with_pixel_data(&origin_image, tpe_image, ".\\test_image.bmp");
	//create_bmp_with_pixel_data(&origin_image, tpe_image, argv[2]);
    return 0;
}