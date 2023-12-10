#include "tpe.h"

unsigned char   *round_n(BMP_File *bmp_file, unsigned char *encry_img, int *random_arr, int block_size, int n)
{
    while (n--)
    {
	    encry_img = substitution(*bmp_file, encry_img);
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