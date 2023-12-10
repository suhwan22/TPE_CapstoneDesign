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

/* get pos(idx) Nth block of (w * h image) */
int	getPosNblock(int w, int h, int bits, int block_size, int n)
{
	int	pos_x, pos_y;

	pos_y = n / (w / block_size);
	pos_x = n - pos_y * (w / block_size);
	return (pos_y * bits * block_size * w + pos_x * block_size * bits);
}

/* 지금은 그저 거꾸로 재배치 한다 규칙을 만들어 넣어주는 걸 고려해봐야 할듯 */
/* 딱 맞아 떨어지는 블록 크기로만 가능 */
unsigned char	*mixBlock(BMP_File *bmp_data, int block_size)
{
    int h;
    int w;
    int idx;
	int	pos;
	int	n;
    unsigned char   *pixel;
    
    w = bmp_data->bmp_infoheader.width;
    h = bmp_data->bmp_infoheader.height;

    pixel = (unsigned char *)malloc(sizeof(unsigned char) * bmp_data->img_size);
    if (!pixel)
    {
		printf("permutation(): malloc failed\n");
        return (NULL);
    }

	n = (w * h) / (block_size * block_size) - 1;

    for (int row = 0; row < h; row += block_size)
    {
		for (int col = 0; col < w; col += block_size)
        {
            if (row + block_size > h || col + block_size > w)
			{
			}
            else
            {
				pos = getPosNblock(w, h, bmp_data->bits, block_size, n--);
				//printf("(%d %d)block -> (%dth)block pos(%d)\n", row, col, n + 1, pos);
                for (int y = row; y < row + block_size; y++)
                {
                	idx = 0;
                    for (int x = col; x < col + block_size; x++)
                    {
                        for (int channel = bmp_data->bits - 1; channel >= 0; channel--)
                        {
                            pixel[pos + idx * bmp_data->bits + channel] \
								= bmp_data->pixel_data[y * bmp_data->bits * w + x * bmp_data->bits + channel];
                        }
						idx++;
                    }
					pos += bmp_data->bits * w;
                }
            }
		}
	}
    return (pixel);
}
