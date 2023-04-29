#include "tpe.h"

unsigned char   *round_n(BMP_File *bmp_file, int *random_arr, int block_size, int n)
{
    unsigned char   *encry_img;

    while (n--)
    {
        printf("round: %d\n", n);
	    encry_img = substitution(*bmp_file, bmp_file->pixel_data);
	    if (!encry_img)
        {
            printf("Error: round_n(): ");
	     	return (NULL);
        }
	    encry_img = permutation(*bmp_file, encry_img, random_arr, block_size);
	    if (!encry_img)
        {
            printf("Error: round_n(): ");
	     	return (NULL);
        }
    }
    return (encry_img);
}