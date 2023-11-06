#include "client.h"

void	init_header(unsigned char *buffer, BMP_FileHeader *fileheader)
{
	fileheader->offset = *(uint16_t*)(&buffer[0]);
	fileheader->size = *(uint32_t*)(&buffer[2]);
	fileheader->reserved1 = *(uint16_t*)(&buffer[6]);
	fileheader->reserved2 = *(uint16_t*)(&buffer[8]);
	fileheader->offset = *(uint32_t*)(&buffer[10]);
}

void	init_infoheader3(unsigned char *buffer, BMP_InfoHeader *infoheader)
{
	infoheader->size = *(uint32_t*)(&buffer[0]);
	infoheader->width = *(int32_t*)(&buffer[4]);
	infoheader->height = *(int32_t*)(&buffer[8]);
	infoheader->planes = *(uint16_t*)(&buffer[12]);
	infoheader->bit_per_pixel = *(uint16_t*)(&buffer[14]);
	infoheader->compression = *(uint32_t*)(&buffer[16]);
	infoheader->size_image = *(uint32_t*)(&buffer[20]);
	infoheader->x_pixels_per_meter = *(int32_t*)(&buffer[24]);
	infoheader->y_pixels_per_meter = *(int32_t*)(&buffer[28]);
	infoheader->colors_used = *(uint32_t*)(&buffer[32]);
	infoheader->colors_important = *(uint32_t*)(&buffer[36]);
}

void	init_infoheader5(unsigned char *buffer, BMP_InfoHeader5 *infoheader)
{
	infoheader->red_channel_mask = *(uint32_t*)(&buffer[0]);
	infoheader->green_channel_mask = *(int32_t*)(&buffer[4]);
	infoheader->blue_channel_mask = *(int32_t*)(&buffer[8]);
	infoheader->alpha_channel_mask = *(int32_t*)(&buffer[12]);
	infoheader->color_space_type = *(int32_t*)(&buffer[16]);
	for (int i = 0; i < 36; i++)
	{
		infoheader->color_space_endpoint[i] = buffer[20 + i];
	}
	infoheader->gamma_red_channel = *(int32_t*)(&buffer[56]);
	infoheader->gamma_green_channel = *(int32_t*)(&buffer[60]);
	infoheader->gamma_blue_channel = *(int32_t*)(&buffer[64]);
	infoheader->intent = *(int32_t*)(&buffer[68]);
	infoheader->ICC_profile_data = *(int32_t*)(&buffer[72]);
	infoheader->ICC_profile_size = *(int32_t*)(&buffer[76]);
	infoheader->reserved = *(int32_t*)(&buffer[80]);
}
