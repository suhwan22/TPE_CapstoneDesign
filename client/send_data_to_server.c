#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "client.h"

#define BUF_SIZE 4096
//expected BUF_SIZE == blocksize(b * b)
//
void	send_data_to_server(int servSock, BMP_File *bmp_data)
{
	unsigned int	data_size = bmp_data->img_size;
	unsigned char	buf[BUF_SIZE] = { 0 };
	unsigned int	i = 0;
	int				end = 128;

	send(servSock, bmp_data->header, 54, 0);
	while (i < data_size)
	{
		if (data_size - i > BUF_SIZE)
			end = BUF_SIZE;
		else
			end = data_size - i;
		for (int j = 0; j < end; j++)
			buf[j] = bmp_data->pixel_data[i + j];
		send(servSock, buf, end, 0);
		//printf("send data: %u\n", i);
		i += BUF_SIZE;
	}
	shutdown(servSock, SHUT_WR);
}
