#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define WAV_HEADER_SIZE 44
#define HDRNAME "wav-header.bin"

int main(int argc, char** argv) {
    uint32_t sampleRate;

    if (argc != 3) {
        printf("Utilizzo: %s <file_wav_input> <file_txt_output>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* wavFile = fopen(argv[1], "rb");
    if (wavFile == NULL) {
        perror("Impossibile aprire il file WAV");
        return EXIT_FAILURE;
    }

    FILE* txtFile = fopen(argv[2], "w");
    if (txtFile == NULL) {
        perror("Impossibile aprire il file di output TXT");
        fclose(wavFile);
        return EXIT_FAILURE;
    }

    FILE* head = fopen(HDRNAME, "wb");
    if (head == NULL) {
        perror("Imposibile aprire il file di output binario");
        fclose(wavFile);
        fclose(txtFile);
        return EXIT_FAILURE;
    }

    uint8_t header[WAV_HEADER_SIZE];
    fread(header, 1, WAV_HEADER_SIZE, wavFile);
    fwrite(header, 1, WAV_HEADER_SIZE, head);

    printf("Inserire la frequenza di campionamento del file wav a 16 bit (Hz): ");
    scanf("%u", &sampleRate);

    int16_t sample;
    double time = 0;

    while (fread(&sample, sizeof(int16_t), 1, wavFile) == 1) {
        fprintf(txtFile, "%.6f\t%d\n", time, sample);
        time += 1.0 / sampleRate;
    }

    fclose(wavFile);
    fclose(txtFile);
    fclose(head);

    printf("Campionamento completato. Dati scritti in %s.\n", argv[2]);

    return EXIT_SUCCESS;
}

