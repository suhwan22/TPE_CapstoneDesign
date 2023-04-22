#include "tpe.h"

unsigned char *permutation(BMP_InfoHeader infoheader, unsigned char *image, int *random_arr, int block_size)
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
    size = 3 * infoheader.width * infoheader.height;
    w = infoheader.width;
    h = infoheader.height;
    pixel = malloc(sizeof(unsigned char) * size + 1);
    if (!pixel)
    {
        printf("Error: permutation(): malloc failed\n");
        return (NULL);
    }
    for (int row = 0; row < h; row += block_size)
    {
		for (int col = 0; col < w; col += block_size)
        {
            idx = 0;
            if (row + block_size >= infoheader.height)
                end_y = infoheader.height;
            else
                end_y = row + block_size;
            for (int y = row; y < end_y; y++)
            {
                if (col + block_size >= infoheader.width)
                    end_x = infoheader.width;
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
    pixel[size] = 0;
    return (pixel);
}