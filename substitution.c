#include "tpe.h"

unsigned char *substitution(BMP_InfoHeader infoheader, unsigned char *image)
{
    int h;
    int w;
    unsigned int    size;
    unsigned char   *pixel;
    unsigned char   a;
    unsigned char   b;
    
    if (!image)
    {
        printf("Error: substitution(): image is NULL\n");
        return (NULL);
    }
    size = 3 * infoheader.width * infoheader.height;
    w = infoheader.width;
    h = infoheader.height;
    pixel = malloc(sizeof(unsigned char) * size + 1);
    if (!pixel)
    {
        printf("Error: substitution(): malloc error\n");
        return (NULL);
    }
    for (int row = 0; row < h; row++)
    {
		for (int col = 0; col < w; col += 2)
        {
			for (int channel = 2; channel >= 0; channel--)
            {
                a = image[row * 3 * w + col * 3 + channel]; 
                b = image[row * 3 * w + (col + 1) * 3 + channel]; 
                if (a + b > 255)
                {
                    pixel[row * 3 * w + col * 3 + channel] = 255 - a;
                    pixel[row * 3 * w + (col + 1) * 3 + channel] = 2 * a + b - 255;
                }
                else
                {
                    pixel[row * 3 * w + col * 3 + channel] = a;
                    pixel[row * 3 * w + (col + 1) * 3 + channel] = b;
                }
			}
		}
	}
    pixel[size] = 0;
    return (pixel);
}
