#include "tpe.h"


int main(void)
{
	// save original bmp file
	BMP_Image	origin_image;

	if (!save_bmp_file(&origin_image, "C:\\Users\\user\\source\\repos\\TPE_test\\lena.bmp"))
	{
		printf("Error: save_bmp_file()\n");
		return (-1);
	}
    printf("width: %d, height: %d\n", origin_image.bmp_infoheader.width, origin_image.bmp_infoheader.height);

	unsigned char	*tpe_image;
	int				*random_arr;
	int				block_size;

	tpe_image = substitution(origin_image.bmp_infoheader, origin_image.pixel_data);
	if (!tpe_image)
		return (-1);
	block_size = 4;
	random_arr = create_random_n_arr(block_size * block_size);
	tpe_image = permutation(origin_image.bmp_infoheader, tpe_image, random_arr, block_size);
	create_bmp_with_pixel_data(&origin_image, tpe_image, "C:\\Users\\user\\source\\repos\\TPE_test\\lenna_cp.bmp");
    return 0;
}