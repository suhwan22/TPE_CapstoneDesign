#include "tpe.h"

unsigned char *inverse_permutation(BMP_File bmp_file, unsigned char *image, int *random_arr, int block_size)
{
    int h;
    int w;
    int idx;
    int end_x;
    int end_y;
    unsigned char   *pixel;
    
    if (!image)
    {
        printf("inverse_permutation(): image is NULL\n");
        return (NULL);
    }
    w = bmp_file.bmp_infoheader.height;
    h = bmp_file.bmp_infoheader.height;
    pixel = malloc(sizeof(unsigned char) * bmp_file.bits * block_size * block_size);
    if (!pixel)
    {
        printf("inverse_permutation(): malloc failed\n");
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
                        for (int channel = bmp_file.bits - 1; channel >= 0; channel--)
                        {
                            if (idx * bmp_file.bits + channel >= block_size * block_size * bmp_file.bits)
                                printf("segfault in load pixel over row: %d, col: %d, idx: %d\n", row, col, idx);
                            if ((row + idx / block_size) * bmp_file.bits * w + (col + idx % block_size) * bmp_file.bits + channel >= \
                                bmp_file.img_size)
                                printf("segfault in load image over row: %d, col: %d, idx: %d\n", row, col, idx);
                            pixel[idx * bmp_file.bits + channel] = image[(row + idx / block_size) * bmp_file.bits * w + (col + idx % block_size) * bmp_file.bits + channel];
                        }
                        idx++;
                    }
                }
                idx = 0;
                for (int y = row; y < row + block_size; y++)
                {
                    for (int x = col; x < col + block_size; x++)
                    {
                        for (int channel = bmp_file.bits - 1; channel >= 0; channel--)
                        {
                            if (idx * bmp_file.bits + channel >= block_size * block_size * bmp_file.bits)
                                printf("segfault in save pixel over row: %d, col: %d, idx: %d\n", row, col, idx);
                            if ((row + random_arr[idx] / block_size) * bmp_file.bits * w + (col + random_arr[idx] % block_size) * bmp_file.bits + channel >= \
                                bmp_file.img_size)
                                printf("segfault in save image over row: %d, col: %d, idx: %d\n", row, col, idx);
                            image[(row + random_arr[idx] / block_size) * bmp_file.bits * w + (col + random_arr[idx] % block_size) * bmp_file.bits + channel] = pixel[idx * bmp_file.bits + channel];
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