#include <stdio.h>
#include <stdlib.h>
#include "opus.h"

#define FALSE 0

const int channels = 1;
const opus_int32 sample_rate = 48000;
const int frame_size_ms = 60;
const int frame_size = 5760;
const int length = channels * frame_size_ms * (sample_rate/1000);

int main(int argc, char const *argv[])
{
    FILE *fp;
    unsigned long fileSize;
    unsigned char *buffer;
    int err;
    OpusDecoder *st;
    opus_int16 out;

    fp = fopen("test.opus", "rb");
    if(!fp) fputs("error opening file", stderr), exit(1);
    
    fseek(fp, 0L, SEEK_END);
    fileSize = ftell(fp);
    rewind(fp);

    buffer = calloc(1, fileSize+1L);
    if(!buffer) fclose(fp), fputs("buffer creation failed", stderr), exit(1);

    if(fread(buffer, fileSize, 1, fp) != 1){
        fclose(fp), free(buffer), fputs("buffer read failed", stderr), exit(1);
    }

    st = opus_decoder_create(sample_rate, channels, &err);
    int frames = opus_decode(st, buffer, length, &out, frame_size, FALSE); // OPUS_INVALID_PACKET
    fprintf(stdout, "decoded %d samples", frames);

    fclose(fp);
    free(buffer);
}
