#include "tpe.h"

unsigned char *substitution(BMP_File bmp_file, unsigned char *image)
{
    int h;
    int w;
    unsigned char   *pixel;
    unsigned char   a;
    unsigned char   b;
    
    if (!image)
    {
        printf("substitution(): image is NULL\n");
        return (NULL);
    }

    w = bmp_file.bmp_infoheader.width;
    h = bmp_file.bmp_infoheader.height;

    pixel = malloc(sizeof(unsigned char) * bmp_file.img_size + 1);
    if (!pixel)
    {
        printf("substitution(): malloc error\n");
        return (NULL);
    }

    for (int row = 0; row < h; row++)
    {
		for (int col = 0; col < w; col += 2)
        {
			for (int channel = bmp_file.bits - 1; channel >= 0; channel--)
            {
                if (col == w - 1) //홀수일 경우 마지막 pixel 처리
                    pixel[row * bmp_file.bits * w + col * bmp_file.bits + channel] = image[row * bmp_file.bits * w + col * bmp_file.bits + channel];
                else
                {
                    a = image[row * bmp_file.bits * w + col * bmp_file.bits + channel];
                    b = image[row * bmp_file.bits * w + (col + 1) * bmp_file.bits + channel];
                    if (a + b > 255 && a + b <= 510 - a)
                    {
                        pixel[row * bmp_file.bits * w + col * bmp_file.bits + channel] = 255 - a;
                        pixel[row * bmp_file.bits * w + (col + 1) * bmp_file.bits + channel] = 2 * a + b - 255;
                    }
                    else
                    {
                        pixel[row * bmp_file.bits * w + col * bmp_file.bits + channel] = a;
                        pixel[row * bmp_file.bits * w + (col + 1) * bmp_file.bits + channel] = b;
                    }
                }
			}
		}
	}
    pixel[bmp_file.img_size] = 0;
    return (pixel);
}
