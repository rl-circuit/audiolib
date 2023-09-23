#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define HEADER_SIZE 44

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Utilizzo: %s <header_binario> <dati_testo> <file_output.wav>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* headerFile = fopen(argv[1], "rb");
    FILE* dataFile = fopen(argv[2], "r");
    FILE* outputFile = fopen(argv[3], "wb");

    if (headerFile == NULL || dataFile == NULL || outputFile == NULL) {
        perror("Errore nell'apertura dei file");
        return EXIT_FAILURE;
    }

    uint8_t header[HEADER_SIZE];
    fread(header, 1, HEADER_SIZE, headerFile);
    fwrite(header, 1, HEADER_SIZE, outputFile);

    double time;
    int16_t amplitude;

    while (fscanf(dataFile, "%lf %hd\n", &time, &amplitude) == 2) {
        fwrite(&amplitude, sizeof(int16_t), 1, outputFile);
    }

    fclose(headerFile);
    fclose(dataFile);
    fclose(outputFile);

    printf("File WAV ricostruito con successo: %s\n", argv[3]);

    return EXIT_SUCCESS;
}

