#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)
typedef struct {
    unsigned char bfType[2];
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BITMAPINFOHEADER;
#pragma pack()

void embedMessage(const char *message, unsigned char *image, int imageSize) {
    int messageLength = strlen(message);
    int messageIndex = 0;
    int bitIndex = 0;

    for (int i = 0; i < imageSize; i++) {
        if (messageIndex < messageLength) {
            image[i] = (image[i] & 0xFE) | ((message[messageIndex] >> bitIndex) & 0x01);
            bitIndex++;
            if (bitIndex == 8) {
                bitIndex = 0;
                messageIndex++;
            }
        } else {
            break;
        }
    }
}

int main() {
    char inputFileName[256];
    char outputFileName[256];
    char message[256];

    printf("Enter input BMP file: ");
    scanf("%255s", inputFileName);

    printf("Enter output BMP file: ");
    scanf("%255s", outputFileName);

    printf("Enter message to embed: ");
    getchar(); // Limpar o buffer do newline restante
    fgets(message, 256, stdin);
    message[strcspn(message, "\n")] = '\0'; // Remover newline do final da mensagem

    FILE *inputFile = fopen(inputFileName, "rb");
    if (!inputFile) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile = fopen(outputFileName, "wb");
    if (!outputFile) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, inputFile);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, inputFile);

    // Verificação dos campos de cabeçalho BMP
    if (fileHeader.bfType[0] != 'B' || fileHeader.bfType[1] != 'M') {
        perror("Not a valid BMP file");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    // Calcular o tamanho da imagem
    int imageSize = infoHeader.biWidth * infoHeader.biHeight * (infoHeader.biBitCount / 8);

    unsigned char *imageData = malloc(imageSize);
    if (imageData == NULL) {
        perror("Error allocating memory");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    fseek(inputFile, fileHeader.bfOffBits, SEEK_SET);
    fread(imageData, 1, imageSize, inputFile);
    fclose(inputFile);

    embedMessage(message, imageData, imageSize);

    fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, outputFile);
    fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, outputFile);
    fseek(outputFile, fileHeader.bfOffBits, SEEK_SET);
    fwrite(imageData, 1, imageSize, outputFile);

    fclose(outputFile);
    free(imageData);

    printf("Message embedded successfully!\n");
    printf("Press Enter to exit...");
    getchar();

    return 0;
}
