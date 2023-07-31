#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include <Windows.h>
#include <math.h>

#define xsize 900
#define ysize 900
#define FILENAME "C:/Users/Park Jiwon/capstone/TPE/test2.bmp"
#define FILENAME2 "C:/Users/Park Jiwon/capstone/TPE/test2_encryption.bmp"
#define BLOCKSIZE 20
#define BLOCKPIXELNUM BLOCKSIZE * BLOCKSIZE
#define CHANNELNUM 3
BITMAPFILEHEADER hf;
BITMAPINFOHEADER hInfo;
RGBQUAD hRGB[256]; // array for palette info
FILE* fp; // file pointer

unsigned char InputImg[xsize][ysize][CHANNELNUM];
unsigned char OutputImg[xsize][ysize][CHANNELNUM];

int irnd(int);
int* PRF();

int main(void) {


	if ((fp = fopen(FILENAME, "rb")) == NULL) {
		printf("READ ERROR");
		exit(0);
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(&hRGB, sizeof(RGBQUAD), 256, fp);
	fread(InputImg, xsize * ysize * CHANNELNUM, 1, fp);
	fclose(fp);


	
	// Divide the image into blocks
	for (int i = 0; i < (xsize / BLOCKSIZE); i++) {
		for (int j = 0; j < (ysize / BLOCKSIZE); j++) {
			for (int k = 0; k < (CHANNELNUM); k++) {

				unsigned short block[BLOCKPIXELNUM];

				for (int x = 0; x < BLOCKSIZE; x++)
					for (int y = 0; y < BLOCKSIZE; y++) {
						//if(InputImg[BLOCKSIZE * i + x][BLOCKSIZE * j + y][k] > 255)
						//	printf("%d\n", InputImg[BLOCKSIZE * i + x][BLOCKSIZE * j + y][k]);
						block[BLOCKSIZE * x + y] = InputImg[BLOCKSIZE * i + x][BLOCKSIZE * j + y][k];
					}
				// Repeat permutations and substitution for rounds
				for (int round = 0; round < 100; round++) {

					// Substitution
					for (int p = 0; p < BLOCKPIXELNUM; p = p + 2) {
						unsigned short a = block[p], b = block[p + 1];
						if ((a + b) > 256) {  
							if (a > 128) {
								if (b < 128) {
									block[p] = 2 * b + a - 256;
									block[p + 1] = 256 - b;
								}
							}
							else {
								if (b > 128) {
									block[p] = 256 - a;
									block[p + 1] = 2 * a + b - 256;
								}
							}
							//block[p] = 256 - a;
							//block[p + 1] = 2 * a + b - 256;
							//if (a + b > 255)
							//	printf("(%d, %d) (%d, %d)\n ", a, b, block[p], block[p + 1]);
						}
					}

					// Pseudo Random Function
					int* PI;
					PI = PRF();

					// Permutation
					for (int x = 0; x < BLOCKSIZE; x++)
						for (int y = 0; y < BLOCKSIZE; y++)
							OutputImg[BLOCKSIZE * i + x][BLOCKSIZE * j + y][k] = *(block + PI[BLOCKSIZE * x + y]);

					for (int x = 0; x < BLOCKSIZE; x++)
						for (int y = 0; y < BLOCKSIZE; y++)
							block[BLOCKSIZE * x + y] = OutputImg[BLOCKSIZE * i + x][BLOCKSIZE * j + y][k];
				}
			}
		}
	}
	
	if ((fp = fopen(FILENAME2, "wb")) == NULL)
		printf("WRITE ERROR");
	fwrite(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(OutputImg, xsize * ysize * CHANNELNUM, 1, fp);
	fclose(fp);
	
	return 0;
}


int* PRF() {
	int i, j, d, a[BLOCKPIXELNUM];

	for (i = 0; i < BLOCKPIXELNUM; i++)
		a[i] = i;

	for (i = BLOCKPIXELNUM - 1; i > 0; i--) {
		j = irnd(i);
		d = a[i]; a[i] = a[j]; a[j] = d;
	}
	return a;
}

int irnd(int n){
	return (int)(rand() % n + 1);
}
