#include "utils.hpp"
#include <iostream>

unsigned char *permutation(BMP_File *bmp_file, unsigned char *image, int *random_arr, int block_size)
{
    int h;
    int w;
    int idx;
    unsigned char   *pixel;
    
    if (!image)
    {
		std::cout << "permutation(): image is NULL" << std::endl;
        return (NULL);
    }

    w = bmp_file->bmp_infoheader.width;
    h = bmp_file->bmp_infoheader.height;

    pixel = (unsigned char *)malloc(sizeof(unsigned char) * bmp_file->bits * block_size * block_size);
    if (!pixel)
    {
		std::cout << "permutation(): malloc failed" << std::endl;
        return (NULL);
    }

    for (int row = 0; row < h; row += block_size)
    {
		for (int col = 0; col < w; col += block_size)
        {
            if (row + block_size > h || col + block_size > w)
                continue;
            else
            {
                idx = 0;
                for (int y = row; y < row + block_size; y++)
                {
                    for (int x = col; x < col + block_size; x++)
                    {
                        for (int channel = bmp_file->bits - 1; channel >= 0; channel--)
                        {
                            if (idx * bmp_file->bits + channel >= block_size * block_size * bmp_file->bits)
                                std::cout << "segfault in save pixel over row: " << row \
									<< ", col: " << col << ", idx: " << idx << std::endl;
                            if ((row + random_arr[idx] / block_size) * bmp_file->bits * w \
									+ (col + random_arr[idx] % block_size) * bmp_file->bits + channel >= bmp_file->img_size)
                                std::cout << "segfault in save pixel over row: " << row \
									<< ", col: " << col << ", idx: " << idx << std::endl;
                            pixel[idx * bmp_file->bits + channel] \
								= image[(row + random_arr[idx] / block_size) * bmp_file->bits * w \
								+ (col + random_arr[idx] % block_size) * bmp_file->bits + channel];
                        }
                        idx++;
                    }
                }
                idx = 0;
                for (int y = row; y < row + block_size; y++)
                {
                    for (int x = col; x < col + block_size; x++)
                    {
                        for (int channel = bmp_file->bits - 1; channel >= 0; channel--)
                        {
                            if (idx * bmp_file->bits + channel >= block_size * block_size * bmp_file->bits)
                                std::cout << "segfault in load pixel over row: " << row \
									<< ", col: " << col << ", idx: " << idx << std::endl;
                            if ((row + idx / block_size) * bmp_file->bits * w \
									+ (col + idx % block_size) * bmp_file->bits + channel >= bmp_file->img_size)
                                std::cout << "segfault in load pixel over row: " << row \
									<< ", col: " << col << ", idx: " << idx << std::endl;
                            image[(row + idx / block_size) * bmp_file->bits * w \
								+ (col + idx % block_size) * bmp_file->bits + channel] 
								= pixel[idx * bmp_file->bits + channel];
                        }
                        idx++;
                    }
                }
            }
		}
	}
    free(pixel);
    return (image);
}
