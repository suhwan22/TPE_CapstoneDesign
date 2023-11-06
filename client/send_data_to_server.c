#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "client.h"

#define BUF_SIZE 10000

void	send_data_to_server(int servSock, BMP_File *bmp_data)
{
	unsigned int	data_size = bmp_data->img_size;
	unsigned char	buf[BUF_SIZE] = { 0 };
	unsigned int	i = 0;
	int				end = BUF_SIZE;

	/* send header info */
	send(servSock, bmp_data->header, 54, 0);

	/* send image pixel_data */
	while (i < data_size)
	{
		if (data_size - i > BUF_SIZE)
			end = BUF_SIZE;
		else
			end = data_size - i;
		for (int j = 0; j < end; j++)
			buf[j] = bmp_data->pixel_data[i + j];
		send(servSock, buf, end, 0);
		i += BUF_SIZE;
	}
	shutdown(servSock, SHUT_WR);
}
