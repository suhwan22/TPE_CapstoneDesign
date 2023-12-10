#include "client.h"

void	init_header(unsigned char *buffer, BMP_FileHeader *fileheader, BMP_InfoHeader *infoheader)
{
	fileheader->offset = *(uint16_t*)(&buffer[0]);
	fileheader->size = *(uint32_t*)(&buffer[2]);
	fileheader->reserved1 = *(uint16_t*)(&buffer[6]);
	fileheader->reserved2 = *(uint16_t*)(&buffer[8]);
	fileheader->offset = *(uint32_t*)(&buffer[10]);
	infoheader->size = *(uint32_t*)(&buffer[14]);
	infoheader->width = *(int32_t*)(&buffer[18]);
	infoheader->height = *(int32_t*)(&buffer[22]);
	infoheader->planes = *(uint16_t*)(&buffer[26]);
	infoheader->bit_count = *(uint16_t*)(&buffer[28]);
	infoheader->compression = *(uint32_t*)(&buffer[30]);
	infoheader->size_image = *(uint32_t*)(&buffer[34]);
	infoheader->x_pixels_per_meter = *(int32_t*)(&buffer[38]);
	infoheader->y_pixels_per_meter = *(int32_t*)(&buffer[42]);
	infoheader->colors_used = *(uint32_t*)(&buffer[46]);
	infoheader->colors_important = *(uint32_t*)(&buffer[50]);
}
