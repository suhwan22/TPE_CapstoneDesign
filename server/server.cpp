#include "server.hpp"
#include "utils.hpp"

Server::Server(int port) : _port(port) {}

Server::~Server() {}

void	Server::serverInit()
{
	struct sockaddr_in	servAddr;

	_servSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(_port);

	if (bind(_servSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) == -1)
	{
		std::cout << "Error: bind()" << std::endl;
		exit(1);
	}

	if (listen(_servSock, 5) == -1)
	{
		std::cout << "Error: listen()" << std::endl;
		exit(1);
	}
}

void	Server::serverStart()
{
	socklen_t			addrSize;
	struct sockaddr_in	clntAddr;
	int					clntSock;

	char	*bmp_data = NULL;

	addrSize = sizeof(clntAddr);
	clntSock = accept(_servSock, (struct sockaddr *)&clntAddr, &addrSize);

	/* setsockopt struct */
	linger optval;
  	optval.l_onoff = 1;
  	optval.l_linger = 1;

	if (setsockopt(clntSock, SOL_SOCKET, SO_LINGER, &optval, sizeof(optval)) == -1)
	{
		std::cout << "Error: serverStart(): setsockopt()" << std::endl;
        close(clntSock);
        exit(1);
    }

	std::cout << "connected client: " << clntSock << std::endl;
	bmp_data = recv_data_from_client(clntSock);
	std::cout << "recv_data_from_client finished" << std::endl;
	save_bmp_data(&_originImage, reinterpret_cast<unsigned char *>(bmp_data));
	std::cout << "save_bmp_data finished" << std::endl;

	unsigned char *img;
	std::string tpe_file_name = "./tpe_file.bmp";

	_originImage.pixel_data = preprocess(&_originImage, _originImage.pixel_data);
	img = tpe(10, 10);
	send_data_to_client(clntSock, &_originImage, img);
	create_bmp_with_pixel_data(&_originImage, img, tpe_file_name.c_str());
	std::cout << "create_bmp_with_pixel_data finished" << std::endl;

	close(_servSock);
	close(clntSock);
}

int	Server::getSock() const
{
	return (_servSock);
}

int	Server::getPort() const
{
	return (_port);
}
