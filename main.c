//
// Created by Tu Fengzhi on 2018/9/30.
//

#include <stdio.h>
#include <stdlib.h>
#include "mmsestsa85.h"

float float_left[SHIFT_SIZE];
float float_right[SHIFT_SIZE];

float InputBuffer[WINDOW_SIZE];
float OutputBuffer[WINDOW_SIZE];

typedef struct header_file
{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate; // sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size; // subchunk2_size denotes the number of samples.
} header;

typedef struct header_file *header_p;

int main()
{
    printf("%f %d\n", 32767.0F, (short)32767.0F);
    FILE *inFile = fopen("../wav/2.wav", "rb");       // Open wave file in read mode
    FILE *outFile = fopen("../wav/2-MMSE.wav", "wb"); // Create output ( wave format) file in write mode

    int count = 0;                                    // For counting number of frames in wave file.
    short buff[WINDOW_SIZE * 2];                      // short int used for 16 bit as input data format is 16 bit PCM audio
    header_p meta = (header_p)malloc(sizeof(header)); // header_p points to a header struct that contains the wave file metadata fields
    unsigned int nb;                                  // variable storing number of byes returned

    if (inFile)
    {
        fread(meta, 1, sizeof(header), inFile);
        fwrite(meta, 1, sizeof(*meta), outFile);
        printf("Size of Header file is %d bytes\n", sizeof(*meta));
        printf("Sampling rate of the input wave file is %uHz\n", meta->sample_rate);
        printf("Number of samples in wave file are %u samples\n", meta->subchunk2_size);

        while (!feof(inFile))
        {
            nb = fread(buff, sizeof(short), SHIFT_SIZE * 2, inFile); // Reading data in chunks of BUFSIZE
            if (nb != 0)
            {
                count++; // Incrementing Number of frames

                for (int i = 0; i < SHIFT_SIZE * 2; i += 2)
                {
                    float_left[i / 2] = (float)buff[i];
                    float_right[i / 2] = (float)buff[i + 1];
                }

                ReadBuffer(float_left, float_right, SHIFT_SIZE, InputBuffer, WINDOW_SIZE);
                MMSESTSA85(InputBuffer, OutputBuffer);
                WriteBuffer(OutputBuffer, WINDOW_SIZE, float_left, float_right, SHIFT_SIZE);

                for (int i = 0; i < SHIFT_SIZE * 2; i += 2)
                {
                    if (float_left[i / 2] > 0)
                    {
                        if (float_left[i / 2] > 32767)
                        {
                            printf("%f %d\n", float_left[i / 2], (short)float_left[i / 2]);
                            float_left[i / 2] = 32767;
                        }
                    }
                    buff[i] = (short)float_left[i / 2];
                    buff[i + 1] = (short)float_left[i / 2];
                }
                fwrite(buff, sizeof(short), nb, outFile); // Writing read data into output file
            }
        }
        printf("\nNumber of frames in the input wave file are %d\n", count);
    }

    return 0;
};