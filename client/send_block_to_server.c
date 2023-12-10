#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "client.h"

#define BUF_SIZE 4096

//이미지 크기가 block 으로 딱 안나눠 떨어지는 경우가 지금 안됨

void	send_block_to_server(int servSock, BMP_File *bmp_data, int block)
{
	unsigned int	data_size = bmp_data->img_size;
	unsigned char	buf[BUF_SIZE] = { 0 };
	unsigned char	*blocks;
	unsigned int	i = 0;
	int				end = BUF_SIZE;

	/* send header info */
	send(servSock, bmp_data->header, 54, 0);

	/* send image pixel_data block  */

	blocks = mixBlock(bmp_data, block);

	while (i < data_size)
	{
		if (data_size - i > BUF_SIZE)
			end = BUF_SIZE;
		else
			end = data_size - i;
		for (int j = 0; j < end; j++)
			buf[j] = blocks[i + j];
		send(servSock, buf, end, 0);
		i += BUF_SIZE;
	}
	shutdown(servSock, SHUT_WR);
}
