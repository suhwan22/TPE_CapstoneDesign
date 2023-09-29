#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "utils.hpp"

#define BUF_SIZE 10000
//expected BUF_SIZE == blocksize(b * b)
//
void	send_data_to_client(int servSock, BMP_File *bmp_data, unsigned char *img)
{
	unsigned int	data_size = bmp_data->img_size;
	unsigned char	buf[BUF_SIZE] = { 0 };
	unsigned int	i = 0;
	int				end = 128;

	while (i < data_size)
	{
		if (data_size - i > BUF_SIZE)
			end = BUF_SIZE;
		else
			end = data_size - i;
		for (int j = 0; j < end; j++)
			buf[j] = img[i + j];
		send(servSock, buf, end, 0);
		//printf("send data: %u\n", i);
		i += BUF_SIZE;
	}
	shutdown(servSock, SHUT_WR);
}
