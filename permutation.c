#include "tpe.h"

unsigned char *permutation(BMP_File bmp_file, unsigned char *image, int *random_arr, int block_size)
{
    int h;
    int w;
    int idx;
    int end_x;
    int end_y;
    unsigned int    size;
    unsigned char   *pixel;
    
    if (!image)
    {
        printf("Error: permutation(): image is NULL\n");
        return (NULL);
    }
    w = bmp_file.bmp_infoheader.width;
    h = bmp_file.bmp_infoheader.height;
    printf("permutation w: %d, h: %d, size: %d\n", w, h, bmp_file.img_size);
    pixel = malloc(sizeof(unsigned char) * size + 1);
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
            idx = 0;
            if (row + block_size >= bmp_file.bmp_infoheader.height)
                end_y = bmp_file.bmp_infoheader.height;
            else
                end_y = row + block_size;
            for (int y = row; y < end_y; y++)
            {
                if (col + block_size >= bmp_file.bmp_infoheader.width)
                    end_x = bmp_file.bmp_infoheader.width;
                else
                    end_x = col + block_size;
                for (int x = col; x < end_x; x++)
                {
			        for (int channel = 2; channel >= 0; channel--)
                    {
                        pixel[y * 3 * w + x * 3 + channel] = image[(row + random_arr[idx] / block_size) * 3 * w + (col + random_arr[idx] % block_size) * 3 + channel];
                    }
                    idx++;
                }
            }
		}
	}
    printf("here?\n");
    pixel[size] = 0;
    return (pixel);
}