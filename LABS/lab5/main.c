#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define UCHAR_MAX  256
#define BYTE_LENGTH 8
#define BUFFER_SIZE_MAX 10000

enum workingMode {
	ENCODE_TEXT = 'c',
	DECODE_TEXT = 'd'
};

typedef struct TTree {
	unsigned char symbol;
	struct TTree* right;
	struct TTree* left;
} TTree;

typedef struct TList {
	int freq;
	TTree* tree;
	struct TList* next;
} TList;

typedef struct THufCode {
	unsigned char symbol;
	char huffmanCode[UCHAR_MAX];
} TCode;

typedef struct TBitBuffer {
	int length;
	char buffer[BUFFER_SIZE_MAX];
} TBitBuffer;

int* BuildFreqTable(FILE* fileIn) {
	int* freqTable = calloc(UCHAR_MAX, sizeof(int));

	unsigned char symbol = '\0';
	while (fread(&symbol, sizeof(char), 1, fileIn) == 1)
		++freqTable[(int)symbol];

	return freqTable;
}

TTree* CreateTree(unsigned char symbol, TTree* left, TTree* right) {
	TTree* new = malloc(sizeof(TTree));
	new->symbol = symbol;
	new->left = left;
	new->right = right;
	return new;
}

void PushToList(int freq, TList** list, TTree* tree) {
	if (((*list) == NULL) || (freq <= (*list)->freq)) {
		TList* node = malloc(sizeof(TList));
		node->tree = tree;
		node->freq = freq;
		node->next = *list;
		*list = node;
	}
	else
		PushToList(freq, &((*list)->next), tree);
}

TList* BuildLeafList(int* freqTable, int* countLeafs) {
	TList* list = NULL;

	for (int i = 0; i < UCHAR_MAX; ++i) {
		if (freqTable[i] > 0) {
			TTree* tree = CreateTree((unsigned char)i, NULL, NULL);
			PushToList(freqTable[i], &list, tree);
			++(*countLeafs);
		}
	}

	return list;
}

TTree* PopList(TList** list) {
	TTree* tree = (*list)->tree;
	TList* box = *list;
	*list = (*list)->next;
	free(box);

	return tree;
}

bool IsListEmpty(TList* list) {
	if (list == NULL)
		return true;
	else
		return false;
}

TTree* BuildHuffmanTree(int* freqTable, TList** list) {
	if ((*list)->next == NULL)
		return (*list)->tree;

	int freq = (*list)->freq;
	TTree* left = PopList(list);
	freq += (*list)->freq;
	TTree* right = PopList(list);
	TTree* tree = CreateTree('\0', left, right);

	PushToList(freq, list, tree);

	return BuildHuffmanTree(freqTable, list);
}

bool IsLeaf(TTree* node) {
	if ((node->left == NULL) && (node->right == NULL))
		return true;
	else
		return false;
}

bool IsTreeEmpty(TTree* tree) {
	if (tree == NULL)
		return true;
	else
		return false;
}

TCode CreateCode(char* huffmanCode, unsigned char symbol) {
	TCode symbolCode = { symbol, {'\0'} };

	for (int i = 0; huffmanCode[i] != '\0'; ++i)
		symbolCode.huffmanCode[i] = huffmanCode[i];

	return symbolCode;
}


void ConvertHTableFromHTree(TTree* tree, TCode* huffmanTable, char* codeSymbol, int i, char bin, int* index) {
	if (i != -1)
		codeSymbol[i] = bin;

	if ((tree->left == NULL) && (tree->right == NULL)) {
		huffmanTable[*index] = CreateCode(codeSymbol, tree->symbol);
		++(*index);
		codeSymbol[i] = '\0';
		return;
	}

	ConvertHTableFromHTree(tree->left, huffmanTable, codeSymbol, i + 1, '0', index);
	ConvertHTableFromHTree(tree->right, huffmanTable, codeSymbol, i + 1, '1', index);
}

TCode* BuildHuffmanTable(TTree* huffmanTree, int countLeafs) {
	char huffmanCode[UCHAR_MAX] = { '\0' };
	int index = 0;
	TCode* huffmanTable = malloc(countLeafs * sizeof(TCode));
	if (countLeafs == 1) {
		huffmanCode[0] = '1';
		huffmanTable[index] = CreateCode(huffmanCode, huffmanTree->symbol);
	}
	else
		ConvertHTableFromHTree(huffmanTree, huffmanTable, huffmanCode, -1, '\0', &index);

	return huffmanTable;
}


void AddBitToBitBuffer(char bit, TBitBuffer* bitBuffer) {
	bitBuffer->buffer[bitBuffer->length] = bit;
	++(bitBuffer->length);
}

void AddSymbolToBitBuffer(unsigned char symbol, TBitBuffer* bitBuffer, int bitsForRead) {
	for (int i = 0; i < bitsForRead; ++i) {
		AddBitToBitBuffer((symbol & 128) == 0 ? '0' : '1', bitBuffer);
		symbol <<= 1;
	}
}

void MoveBitBuffer(TBitBuffer* bitBuffer, int shift) {
	for (int i = 0; i < bitBuffer->length; ++i)
		bitBuffer->buffer[i] = bitBuffer->buffer[i + shift];
	bitBuffer->length -= shift;
}

unsigned char CompressBitBufferToSymbol(TBitBuffer* bitBuffer) {
	unsigned char encodedSymbol = 0;
	for (int i = 0; i < BYTE_LENGTH; ++i) {
		encodedSymbol <<= 1;
		encodedSymbol |= (bitBuffer->buffer[i] == '1' ? 1 : 0);
	}
	MoveBitBuffer(bitBuffer, BYTE_LENGTH);
	return encodedSymbol;
}

void PrintEncodedSymbol(TBitBuffer* bitBuffer, FILE* fileOut) {
	unsigned char encodedTree = CompressBitBufferToSymbol(bitBuffer);
	fprintf(fileOut, "%c", encodedTree);
}

void OutputHuffmanTree(TTree* tree, TBitBuffer* bitBuffer, FILE* fileOut) {
	if (IsLeaf(tree)) {
		AddBitToBitBuffer('1', bitBuffer);
		AddSymbolToBitBuffer(tree->symbol, bitBuffer, BYTE_LENGTH);
		PrintEncodedSymbol(bitBuffer, fileOut);
		return;
	}
	AddBitToBitBuffer('0', bitBuffer);
	OutputHuffmanTree(tree->left, bitBuffer, fileOut);
	OutputHuffmanTree(tree->right, bitBuffer, fileOut);

	while (bitBuffer->length >= BYTE_LENGTH) 
		PrintEncodedSymbol(bitBuffer, fileOut);
}

void AddSymbolCodeToBitBuffer(TCode code, TBitBuffer* bitBuffer) {
	for (int i = 0; code.huffmanCode[i] != '\0'; ++i) 
		AddBitToBitBuffer(code.huffmanCode[i], bitBuffer);
}

void AppendNullBits(TBitBuffer* bitBuffer) {
	for (int i = bitBuffer->length; i < BYTE_LENGTH; ++i) {
		AddBitToBitBuffer('0', bitBuffer);
	}
}

void PrintCountNullBits(TBitBuffer* bitBuffer, FILE* fileOut) {
	int filePosition = ftell(fileOut);
	fseek(fileOut, 0, SEEK_SET);
	char countNullBits = (BYTE_LENGTH - (char)bitBuffer->length) % 8;
	fprintf(fileOut, "%c", countNullBits);
	fseek(fileOut, filePosition, SEEK_SET);
}

void OutputEncodedText(FILE* fileIn, FILE* fileOut, TBitBuffer* bitBuffer, TCode* huffmanTable, int countLeafs) {
	fseek(fileIn, 1, SEEK_SET);
	unsigned char encodedSymbol = '\0';
	while (fread(&encodedSymbol, sizeof(unsigned char), 1, fileIn) == 1) {
		for (int i = 0; i < countLeafs; ++i) {
			if (huffmanTable[i].symbol == encodedSymbol) 
				AddSymbolCodeToBitBuffer(huffmanTable[i], bitBuffer);
		}
		while (bitBuffer->length >= BYTE_LENGTH)
			PrintEncodedSymbol(bitBuffer, fileOut);
	}
	PrintCountNullBits(bitBuffer, fileOut);
	if (bitBuffer->length != 0) {
		AppendNullBits(bitBuffer);
		PrintEncodedSymbol(bitBuffer, fileOut);
	}
}

void CompleteHuffmanTree(TBitBuffer* bitBuffer, FILE* fileOut) {
	if (bitBuffer->length == 0)
		return;

	AppendNullBits(bitBuffer);

	unsigned char encodedSymbol = CompressBitBufferToSymbol(bitBuffer);
	fprintf(fileOut, "%c", encodedSymbol);
}



void DestroyTree(TTree* tree) {
	if (!IsTreeEmpty(tree)) {
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		free(tree);
	}
}

void FreeEncodeMemory(int* freqTable, TList* list, TTree* tree, TCode* huffmanTable) {
	free(freqTable);
	free(list);
	DestroyTree(tree);
	free(huffmanTable);
}

void Encode(FILE* fileIn, FILE* fileOut) {
	int countLeafs = 0;

	int* freqTable = BuildFreqTable(fileIn);
	TList* list = BuildLeafList(freqTable, &countLeafs);

	if (IsListEmpty(list)) {
		free(freqTable);
		return;
	}

	TTree* huffmanTree = BuildHuffmanTree(freqTable, &list);
	TCode* huffmanTable = BuildHuffmanTable(huffmanTree, countLeafs);
	TBitBuffer bitBuffer = { 0, {'\0'} };

	fprintf(fileOut, " ");
	OutputHuffmanTree(huffmanTree, &bitBuffer, fileOut);
	CompleteHuffmanTree(&bitBuffer, fileOut);
	
	OutputEncodedText(fileIn, fileOut, &bitBuffer, huffmanTable, countLeafs);
	
	FreeEncodeMemory(freqTable, list, huffmanTree, huffmanTable);
}

char InputCountNullBits(FILE* fileIn) {
	char countNullBits = 0;
	if (fscanf(fileIn, "%c", &countNullBits) != 1)
		exit(0);
	return countNullBits;
}

TTree* RebuildHuffmanTree(FILE* fileIn, TBitBuffer* bitBuffer) {
	if (bitBuffer->length == 0) {
		unsigned char encodedSymbol = fgetc(fileIn);
		AddSymbolToBitBuffer(encodedSymbol, bitBuffer, BYTE_LENGTH);
	}

	if (bitBuffer->buffer[0] == '1') {
		MoveBitBuffer(bitBuffer, 1);
		if (bitBuffer->length < BYTE_LENGTH) {
			unsigned char encodedSymbol = fgetc(fileIn);
			AddSymbolToBitBuffer(encodedSymbol, bitBuffer, BYTE_LENGTH);
		}
		unsigned char decodedSymbol = CompressBitBufferToSymbol(bitBuffer);
		TTree* node = CreateTree(decodedSymbol, NULL, NULL);
		return node;
	}
	else {
		MoveBitBuffer(bitBuffer, 1);
		TTree* left = RebuildHuffmanTree(fileIn, bitBuffer);
		TTree* right = RebuildHuffmanTree(fileIn, bitBuffer);
		TTree* tree = CreateTree('\0', left, right);
		return tree;
	}
}

void OutputDecodedText(TTree* root, TBitBuffer* bitBuffer, int countNullBits, FILE* fileIn, FILE* fileOut) {
	MoveBitBuffer(bitBuffer, bitBuffer->length);

	unsigned char firstSymbol = fgetc(fileIn);
	unsigned char secondSymbol = '\0';
	bool statusRead = true;
	int count = BYTE_LENGTH;
	TTree* huffmanTree = root;

	while (statusRead) {
		if (fread(&secondSymbol, sizeof(unsigned char), 1, fileIn) != 1) {
			statusRead = false;
			count -= (int)countNullBits;
		}
		AddSymbolToBitBuffer(firstSymbol, bitBuffer, count);
		for (int i = 0; i < count; ++i) {
			huffmanTree = (bitBuffer->buffer[0] == '0' ? huffmanTree->left : huffmanTree->right);
			MoveBitBuffer(bitBuffer, 1);
			if (IsTreeEmpty(huffmanTree)) {
				huffmanTree = root;
			}
			if (IsLeaf(huffmanTree)) {
				fprintf(fileOut, "%c", huffmanTree->symbol);
				huffmanTree = root;
			}
		}
		firstSymbol = secondSymbol;
	}
}

void Decode(FILE* fileIn, FILE* fileOut) {
	char countNullBits = InputCountNullBits(fileIn);

	TBitBuffer bitBuffer = { 0, {"\0"} };
	TTree* HuffmanTree = RebuildHuffmanTree(fileIn, &bitBuffer);

	OutputDecodedText(HuffmanTree, &bitBuffer, countNullBits, fileIn, fileOut);

	DestroyTree(HuffmanTree);
}

int main() {
	FILE* fileIn = fopen("in.txt", "rb");
	FILE* fileOut = fopen("out.txt", "wb");

	unsigned char workingMode = fgetc(fileIn);

	switch (workingMode) {
	case ENCODE_TEXT:
		Encode(fileIn, fileOut);
		break;
	case DECODE_TEXT:
		Decode(fileIn, fileOut);
		break;
	default:
		break;
	}

	fclose(fileIn);
	fclose(fileOut);
}
