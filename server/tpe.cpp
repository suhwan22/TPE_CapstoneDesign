#include "server.hpp"
#include "utils.hpp"

unsigned char	*Server::tpe(int block_size, int round)
{
	unsigned char	*tpe_image;
	int				*random_arr;

	random_arr = create_random_n_arr(block_size * block_size);
	tpe_image = _originImage.pixel_data;

	tpe_image = round_n(&_originImage, tpe_image, random_arr, block_size, round);
    return tpe_image;
}

