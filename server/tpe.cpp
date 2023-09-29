#include "server.hpp"
#include "utils.hpp"

void	Server::tpe()
{
	unsigned char	*tpe_image;
	int				*random_arr;
	int				block_size;

	clock_t	start = clock();
	block_size = 16;
	random_arr = create_random_n_arr(block_size * block_size);
	tpe_image = _originImage.pixel_data;

	tpe_image = round_n(&_originImage, tpe_image, random_arr, block_size, 10);
	create_bmp_with_pixel_data(&_originImage, tpe_image, "./tpe_food.bmp");
	printf("\ntime : %d\n", clock() - start);
	free(tpe_image);
    return 0;
}

