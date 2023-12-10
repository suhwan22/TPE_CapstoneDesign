#include "client.h"
#include <unistd.h>

int main(int argc, char **argv)
{
	BMP_File	origin_image;
	unsigned char	*tpe_image;
	int				servSock;

	if (argc != 4)
	{
		printf("Usage: %s <ip> <port> <bmp_file_path>\n", argv[0]);
		exit(1);
	}

	clock_t	start = clock();
	if (!save_bmp_file(&origin_image, argv[3]))
		exit (1);
    printf("width: %d, height: %d\n", origin_image.bmp_infoheader.width, origin_image.bmp_infoheader.height);
	printf("pixels: %d\n", origin_image.bits);
	printf("image total size: %u\n", origin_image.img_size);

	servSock = connect_server(argv[1], atoi(argv[2]));
	send_data_to_server(servSock, &origin_image);
	//send_block_to_server(servSock, &origin_image, 10);
	tpe_image = recv_data_from_server(servSock);
	if (!tpe_image)
		exit(1);

	create_bmp_with_pixel_data(&origin_image, tpe_image, "./tpe_image.bmp");
	printf("\ntime : %ld\n", clock() - start);
	free(tpe_image);
	close(servSock);
    return 0;
}
