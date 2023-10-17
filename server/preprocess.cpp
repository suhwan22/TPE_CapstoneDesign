#include "utils.hpp"
#include <iostream>

unsigned char *preprocess(BMP_File *bmp_file, unsigned char *image)
{
    int h;
    int w;
    unsigned char   *pixel;
    unsigned char   a;
    unsigned char   b;
    

	int	temp_key[256];

	srand(time(NULL));
	for (int t = 0; t < 256; t++)
		temp_key[t] = rand() % 256;

    if (!image)
    {
    	std::cout << "substitution(): image is NULL" << std::endl;
        return (NULL);
    }

    w = bmp_file->bmp_infoheader.width;
    h = bmp_file->bmp_infoheader.height;

    pixel = (unsigned char *)malloc(sizeof(unsigned char) * bmp_file->img_size + 1);
    if (!pixel)
    {
		std::cout << "substitution(): malloc error" << std::endl;
        return (NULL);
    }

	int	cnt = 0;
	int	k = 0;

    for (int row = 0; row < h; row++)
    {
		for (int col = 0; col < w; col += 2)
        {
			for (int channel = bmp_file->bits - 1; channel >= 0; channel--)
            {
                if (col == w - 1) //홀수일 경우 마지막 pixel 처리
                    pixel[row * bmp_file->bits * w + col * bmp_file->bits + channel] \
						= image[row * bmp_file->bits * w + col * bmp_file->bits + channel];
                else
                {
                    a = image[row * bmp_file->bits * w + col * bmp_file->bits + channel];
                    b = image[row * bmp_file->bits * w + (col + 1) * bmp_file->bits + channel];
                    if (a + b > temp_key[cnt % 256])
					{
						if (a < temp_key[cnt % 256] && a + b <= 2 * temp_key[cnt % 256] - a)
						{
	                        pixel[row * bmp_file->bits * w + col * bmp_file->bits + channel] = temp_key[cnt % 256] - a;
	                        pixel[row * bmp_file->bits * w + (col + 1) * bmp_file->bits + channel] = 2 * a + b - temp_key[cnt % 256];
						}
						else
						{
	                        pixel[row * bmp_file->bits * w + col * bmp_file->bits + channel] = a;
	                        pixel[row * bmp_file->bits * w + (col + 1) * bmp_file->bits + channel] = b;

						}
                    }
                    else
					{
						k = temp_key[cnt % 256] % ((int)a + (int)b);
						if (a < k)
						{
	                        pixel[row * bmp_file->bits * w + col * bmp_file->bits + channel] = k - a;
	                        pixel[row * bmp_file->bits * w + (col + 1) * bmp_file->bits + channel] = 2 * a + b - k;
						}
						else
						{
	                        pixel[row * bmp_file->bits * w + col * bmp_file->bits + channel] = a;
	                        pixel[row * bmp_file->bits * w + (col + 1) * bmp_file->bits + channel] = b;
						}
                    }
                }
			}
			cnt++;
		}
	}
    pixel[bmp_file->img_size] = 0;
    return (pixel);
}
