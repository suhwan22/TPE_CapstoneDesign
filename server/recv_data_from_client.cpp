#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "utils.hpp"

#define BUF_SIZE 4096

char	*recv_data_from_client(int clntSock)
{
	char	buf[BUF_SIZE] = { 0 };
	char	*temp;
	unsigned int	size = 0;
	int				strlen;

	temp = (char *)malloc(sizeof(char) * 2);
	if (!temp)
	{
		std::cout << "Error: recv_data_from_server(): malloc()" << std::endl;
		exit(1);
	}
	while (1)
	{
		strlen = recv(clntSock, buf, BUF_SIZE, 0);
		if (strlen == -1)
		{
			std::cout << "Error: recv_data_from_client(): recv()" << std::endl;
			return (NULL);
		}

		if (strlen == 0)
		{
			std::cout << "finished recv: " << clntSock << std::endl;
			shutdown(clntSock, SHUT_WR);
			break;
		}
		else
		{
			std::cout << "recv size: " << size << std::endl;
			temp = my_strjoin(temp, buf, size, strlen);
			size += strlen;
		}
	}
	return (temp);
}

