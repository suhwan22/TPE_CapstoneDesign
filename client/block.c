#include <stdio.h>
#include <stdlib.h>
#include "client.h"

/* bmp_file : origin bmp_file, n : #n block in image */
/* return Nth block of bmp_file->pixel_data, size: block_size * block_size */

unsigned char *getNthBlock(BMP_File *bmp_file, int n, int block_size, unsigned int *return_size)
{
    int h;
    int w;
    int idx;
	int	begin_row;
	int	begin_col;
    unsigned char   *pixel;
	unsigned char	*image;

    w = bmp_file->bmp_infoheader.width;
    h = bmp_file->bmp_infoheader.height;
	image = bmp_file->pixel_data;

	begin_row = (n / (w / block_size)) ;
	begin_col = n - begin_row * (w / block_size);

	pixel = (unsigned char *)malloc(sizeof(unsigned char) * bmp_file->bits * block_size * block_size);
	if (!pixel)
	{
		printf("getNthBlock(): malloc failed\n");
		return (NULL);
	}
	idx = 0;
    for (int y = begin_row; y < begin_row + block_size; y++)
    {
        for (int x = begin_col; x < begin_col + block_size; x++)
        {
            for (int channel = bmp_file->bits - 1; channel >= 0; channel--)
            {
                pixel[idx * bmp_file->bits + channel] \
					= image[y * bmp_file->bits * w \
					+ x * bmp_file->bits + channel];
            }
            	idx++;
        }
	}
	*return_size = bmp_file->bits * block_size * block_size;;
    return (pixel);
}
