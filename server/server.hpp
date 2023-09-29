#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <unistd.h>
# include <string>
# include <cstring>
# include <vector>
# include <arpa/inet.h>
# include "bmp.hpp"

# define BUF_SIZE 100
# define EPOLL_SIZE 50

class Server
{
	private:
		BMP_File				_originImage;
		int						_servSock;
		int						_port;

	public:
		Server(int port);
		~Server();

		//Server& operator=(const Server& obj);
		void	tpe();

		void	serverInit();
		void	serverStart();

		int		getSock() const;
		int		getPort() const;

};

#endif
