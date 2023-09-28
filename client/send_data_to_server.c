#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BUF_SIZE 128
//expected BUF_SIZE == blocksize(b * b)

void	send_data_to_server(int servSock, unsigned char *pixel_data, unsigned int data_size)
{
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
			buf[j] = pixel_data[i + j];
		send(servSock, buf, end, 0);
		i += BUF_SIZE;
	}
	shutdown(servSock, SHUT_WR);
}
