#include "tpe.h"

unsigned char *permutation(BMP_File bmp_file, unsigned char *image, int *random_arr, int block_size)
{
    int h;
    int w;
    int idx;
    int end_x;
    int end_y;
    unsigned char   *pixel;
    
    if (!image)
    {
        printf("Error: permutation(): image is NULL\n");
        return (NULL);
    }
    w = bmp_file.bmp_infoheader.width;
    h = bmp_file.bmp_infoheader.height;
    printf("permutation w: %d, h: %d, size: %d\n", w, h, bmp_file.img_size);
    pixel = malloc(sizeof(unsigned char) * bmp_file.bits * block_size * block_size);
    if (!pixel)
    {
        printf("Error: permutation(): malloc failed\n");
        return (NULL);
    }
    for (int i = 0; i < block_size; i++)
    {
        for (int j = 0; j < block_size; j++)
            printf("%4d ", random_arr[i * block_size + j]);
        printf("\n");
    }
    for (int row = 0; row < h; row += block_size)
    {
		for (int col = 0; col < w; col += block_size)
        {
            if (row + block_size > h || col + block_size > w)
            {
                //printf("edge case: row, col(%d, %d)\n", row, col);
                continue;
            }
            else
            {
                idx = 0;
                for (int y = row; y < row + block_size; y++)
                {
                    for (int x = col; x < col + block_size; x++)
                    {
                        //printf("current row: %d, col: %d, idx: %d\n", row, col, idx);
                        for (int channel = bmp_file.bits - 1; channel >= 0; channel--)
                        {
                            pixel[idx * bmp_file.bits + channel] = image[(row + random_arr[idx] / block_size) * bmp_file.bits * w + (col + random_arr[idx] % block_size) * bmp_file.bits + channel];
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
                            image[y * bmp_file.bits * w + x * bmp_file.bits + channel] = pixel[idx * bmp_file.bits + channel];
                        }
                        idx++;
                    }
                }
            }
		}
	}
    //printf("here?\n");
    free(pixel);
    return (image);
}