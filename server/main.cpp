#include "server.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
		exit(1);
	}
	Server server(atoi(argv[1]));
	server.serverInit();
	server.serverStart();
	return (0);
}
