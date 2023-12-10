#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "client.h"

#define BUF_SIZE 10000
//expected BUF_SIZE == blocksize(b * b)

unsigned char	*recv_data_from_server(int servSock)
{
	unsigned char	buf[BUF_SIZE] = { 0 };
	unsigned char	*temp;
	unsigned int	size = 0;
	int				strlen;

	temp = malloc(sizeof(unsigned char) * 2);
	if (!temp)
	{
		printf("Error: recv_data_from_server(): malloc()\n");
		exit(1);
	}
	while (1)
	{
		strlen = recv(servSock, buf, BUF_SIZE, 0);
		if (strlen == -1)
		{
			printf("Error: recv_data_from_server(): recv()\n");
			return (NULL);
		}

		if (strlen == 0)
		{
			printf("finished recv size: %d\n", size);
			close(servSock);
			break;
		}
		else
		{
			temp = my_join(temp, buf, size, strlen);
			size += strlen;
		}
	}
	shutdown(servSock, SHUT_RD);
	return (temp);
}
