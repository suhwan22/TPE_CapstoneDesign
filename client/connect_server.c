#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

int	connect_server(char *ip, int port)
{
	int servSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (servSocket == -1)
	{
		printf("Failed create Clent Socket\n");
		exit(1);
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);

	if (inet_pton(AF_INET, ip, &serverAddr.sin_addr.s_addr) <= 0)
	{
		printf("Error: Invalid server ID: %d\n", serverAddr.sin_addr.s_addr);
		exit(1);
	}

	if (connect(servSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
	{
		printf("Failed conneting Server\n");
		close(servSocket);
		exit(1);
	}

	return (servSocket);
}
