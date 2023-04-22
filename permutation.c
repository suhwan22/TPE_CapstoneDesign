#include "tpe.h"

unsigned char *permutation(BMP_InfoHeader infoheader, unsigned char *image, int *random_arr, int block_size)
{
    int h;
    int w;
    int idx;
    unsigned int    size;
    unsigned char   *pixel;
    
    if (!image)
    {
        printf("Error: permutation(): image is NULL\n");
        return (NULL);
    }
    size = 3 * infoheader.width * infoheader.height;
    w = infoheader.width;
    h = infoheader.height;
    pixel = malloc(sizeof(unsigned char) * size + 1);
    for (int row = 0; row < h; row += block_size)
    {
		for (int col = 0; col < w; col += block_size)
        {
            idx = 0;
            for (int y = row; y < row + block_size; y++)
            {
                for (int x = col; x < col + block_size; x++)
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
    pixel[size] = 0;
    return (pixel);
}