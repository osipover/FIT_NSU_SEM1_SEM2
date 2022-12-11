#include <stdio.h>
#define SIZE_SAMPLE 17

void ReadSample(FILE* file, unsigned char* sample, int* lengthSample);
int GetHash(unsigned char* sample, int lengthSample, int* degree);
int ReadText(FILE* file, unsigned char* buffer, int lengthSample);
void CompareSymbols(unsigned char* buffer, unsigned char* sample, int position, int lengthSample);
int GetNextHash(FILE* file, unsigned char* buffer, int* bufferHash, int lengthSample, int* degree);
void RabinKarpAlgorithm(FILE* file, unsigned char* sample, int lengthSample, int sampleHash, int* degree);

int main() {
    FILE* file = fopen("in.txt", "r");
    unsigned char sample[SIZE_SAMPLE];
    int lengthSample = 0, degree;
    ReadSample(file, sample, &lengthSample);
    int sampleHash = GetHash(sample, lengthSample, &degree);
    RabinKarpAlgorithm(file, sample,  lengthSample, sampleHash, &degree);
    fclose(file);
    return 0;
}

void ReadSample(FILE* file, unsigned char* sample, int* lengthSample) {
    for (int i = 0; i < SIZE_SAMPLE; ++i) {
        sample[i] = fgetc(file);
        if (sample[i] == '\n') {
            sample[i] = '\0';
            break;
        }
        (*lengthSample)++;
    }
}

int GetHash(unsigned char* sample, int lengthSample, int* degree) {
    int hash = 0;
    *degree = 1;
    for (int i = 0; i < lengthSample; ++i) {
        hash += ((int)sample[i] % 3) * (*degree);
        (*degree) *= 3;
    }
    (*degree) /= 3;
    return hash;
}

int ReadText(FILE* file, unsigned char* buffer, int lengthSample) {
    int i = 0;
    for (int j = 1; j < lengthSample; ++j) {
        buffer[i] = buffer[j];
        ++i;
    }
    if (!fread(buffer + lengthSample - 1, sizeof(unsigned char), 1, file))
        return 0;
    if (feof(file))
        return 0;
    return 1;
}

int GetNextHash(FILE* file, unsigned char* buffer, int* bufferHash, int lengthSample, int* degree) {
    *bufferHash -= (int)buffer[0] % 3;
    if (ReadText(file, buffer, lengthSample) == 0)
        return 0;
    *bufferHash /= 3;
    *bufferHash += (int)buffer[lengthSample - 1] % 3 * (*degree);
    return 1;
}

void CompareSymbols(unsigned char* buffer, unsigned char* sample, int position, int lengthSample) {
    for (int i = 0; i < lengthSample; ++i) {
        if (buffer[i] == sample[i])
            printf("%d ", position + i);
        else {
            printf("%d ", position + i);
            break;
        }
    }
}

void RabinKarpAlgorithm(FILE* file, unsigned char* sample, int lengthSample, int sampleHash, int* degree) {
    printf("%d ", sampleHash);
    unsigned char buffer[SIZE_SAMPLE];
    int position = 1;
    if (!fread(buffer, sizeof(unsigned char), lengthSample, file))
        return;
    if (feof(file))
        return;
    int bufferHash = GetHash(buffer, lengthSample, degree);
    while (1) {
        if (sampleHash == bufferHash)
            CompareSymbols(buffer, sample, position, lengthSample);
        if (GetNextHash(file, buffer, &bufferHash, lengthSample, degree) == 0)
            break;
        position++;
    }
}
