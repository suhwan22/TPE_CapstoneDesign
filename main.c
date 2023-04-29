#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

struct chunk {
    unsigned char chunk_name[4];
    unsigned char chunk_type[4];
    unsigned char* chunk_data;
    unsigned long chunk_size;
    unsigned char crc[4];
};

int main() {

    FILE* fp;
    fp = fopen("C:\\Project\\source\\testp.png", "rb");

    unsigned char header[8];
    int data_num;
    struct chunk chunk[10];

    if (fp == NULL) {
        printf("error: can't find file\n");
        return 1;
    }

    if (fread(header, 1, 8, fp) != 8) {
        printf("header error");
        return 1;
    }
   
    for (int j = 0; j < 8; j++) {
        if (fread(chunk[j].chunk_name, 1, 4, fp) != 4) {
            printf("chumk error");
            return 1;
        }

        chunk[j].chunk_size = ((chunk[j].chunk_name[0] << 24) | (chunk[j].chunk_name[1] << 16) | (chunk[j].chunk_name[2] << 8) | chunk[j].chunk_name[3]);
        printf("%d\n", chunk[j].chunk_size);


        if (fread(chunk[j].chunk_type, 1, 4, fp) != 4) {
            printf("IHDR_type error");
            return 1;
        }
        else {
            printf("%s\n", chunk[j].chunk_type);
        }



        chunk[j].chunk_data = (unsigned char*)malloc(sizeof(char) * chunk[j].chunk_size);

        if (fread(chunk[j].chunk_data, 1, chunk[j].chunk_size, fp) != (chunk[j].chunk_size)) {
            printf("data error");
            return 1;
        }
     
            /*
        printf("width: %d\n", ((chunk[j].chunk_data[0] << 24) | (chunk[j].chunk_data[1] << 16) | (chunk[j].chunk_data[2] << 8) | chunk[j].chunk_data[3]));
        printf("heigth: %d\n", ((chunk[j].chunk_data[4] << 24) | (chunk[j].chunk_data[5] << 16) | (chunk[j].chunk_data[6] << 8) | chunk[j].chunk_data[7]));
        printf("bit depth: %x\n", chunk[j].chunk_data[8]);
        printf("color Type: %x\n", chunk[j].chunk_data[9]);
        printf("compression: %x\n", chunk[j].chunk_data[10]);
        printf("filter: %x\n", chunk[j].chunk_data[11]);
        printf("interace: %x\n", chunk[j].chunk_data[12]);
        */
     

        if (fread(chunk[j].crc, 1, 4, fp) != 4) {
            printf("crc error");
            return 1;
        }

        
        printf("-------------------------\n");
        if (strncmp((const char*)chunk[j].chunk_type, "IEND", 4) == 0) {
            j = 10;
        }
    }
  
    for (int i = 0; i < 10; i++) {
        if (strncmp((const char*)chunk[i].chunk_type, "IDAT",4) == 0) {
            data_num = i;
            break;
        }
    }

    return 0;

}
/*
int decode_filtered_data(unsigned char* data, int width, int heigth){
    unsigned char* prev_row = NULL;
    
    for (int i = 0; i < heigth; i++) {

        unsigned char filter_type = data[i * (width)+1];
        for (int j = 1; j < width + 1; j++) {
            unsigned char a, b, c;
            if (i == 0) {
                a = b = c = 0;
            }
            else {
                a = prev_row[j - 1];
                b = prev_row[j];
                c = prev_row[j + 1];
            }

            switch (filter_type) {
            case 0:  // None
                break;
            case 1:  // Sub
                data[i * (width + 1) + j] += a;
                break;
            case 2:  // Up
                data[i * (width + 1) + j] += b;
                break;
            case 3:  // Average
                data[i * (width + 1) + j] += (a + b) / 2;
                break;
            case 4:  // Paeth
                data[i * (width + 1) + j] += PaethPredictor(a, b, c);
                break;
            }
        }

        prev_row = &data[i * (width + 1)];
    }

    return 0;

}*/