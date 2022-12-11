#include <stdio.h>
#define SIZE_SAMPLE 17

void readSample(FILE* file, unsigned char* sample, int* lengthSample);
void buildTableShift(int* shiftTable, unsigned char* sample, int lengthSample);
int scanString(FILE* file, unsigned char* buffer, int size, int lengthSample);
int BoyerMoor(FILE* file, int lengthSample, unsigned char* sample, int* shiftTable);

int main() {
    FILE* file = fopen("in.txt", "r");
    unsigned char sample[SIZE_SAMPLE];
    int lengthSample = 0;
    readSample(file, sample, &lengthSample);
    int shiftTable[256];
    buildTableShift(shiftTable, sample, lengthSample);
    BoyerMoor(file, lengthSample, sample, shiftTable);
    fclose(file);
    return 0;
}

void readSample(FILE* file, unsigned char* sample, int* lengthSample) {
    for (int i = 0; i < SIZE_SAMPLE; ++i) {
        sample[i] = fgetc(file);
        if (sample[i] == '\n') {
            sample[i] = '\0';
            break;
        }
        (*lengthSample)++;
    }
}

void buildTableShift(int* shiftTable, unsigned char* sample, int lengthSample) {
    for (int i = 0; i < 256; ++i)
        shiftTable[i] = lengthSample;
    for (int i = lengthSample - 2; i >= 0; --i) {
        int symbol = (int)sample[i];
        if (shiftTable[symbol] == lengthSample) {
            shiftTable[symbol] = lengthSample - i - 1;
        }
    }
}


int scanString(FILE* file, unsigned char* buffer, int size, int lengthSample) {
    int i = 0;
    for (int j = size; j < lengthSample; ++j) {
        buffer[i] = buffer[j];
        ++i;
    }
    size = lengthSample - i;
    if (!fread(buffer + i, sizeof(unsigned char), size, file))
        return 0;
    if (feof(file))
        return 0;
    return 1;
}

int BoyerMoor(FILE* file, int lengthSample, unsigned char* sample, int* shiftTable) {
    unsigned char buffer[SIZE_SAMPLE];
    if (!scanString(file, buffer, lengthSample, lengthSample))
        return 0;
    int position = 0;
    while (1) {
        int shift = 0;
        for (int i = lengthSample - 1; i >= 0; --i) {
            printf("%d ", i + position + 1);
            if ((buffer[i] != sample[i]) || (i == 0))
                break;
        }
        shift = shiftTable[(int)buffer[lengthSample - 1]];
        position += shift;
        if (!scanString(file, buffer, shift, lengthSample))
            return 0;
    }
}
