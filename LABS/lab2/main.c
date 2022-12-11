#include <stdio.h>
#include <string.h>
int FindMaxIndex(char * Nummer, int size)
{
    for (int i = size-2; i >= 0; --i)
        if (Nummer[i] < Nummer[i+1])
            return i;
    return -1;
}

int FindBiggerElement(char * Nummer, int size, int IndexMaxEl)
{
    int Element = IndexMaxEl;
    for (int i = size-1; i >= 0; --i)
    {
        if (Nummer[i] > Nummer[Element])
            return i;
    }
    return -1;
}


void swap(char* a, char* b)
{
	char t = *a;
	*a = *b;
	*b = t;
}

void reverse(char * arr, int size)
{
	for (int i = 0; i < size/2; ++i)
	{
		swap(&arr[i], &arr[size - i - 1]);	
	}
}

int CheckOrder(char * Nummer, int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        if (Nummer[i] < Nummer[i+1])
            return 0;
        else
            continue;
    }
    return -1;
}

int CheckElements(char * Nummer, int size)
{
    int CheckEl[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < size; ++i)
    {
        int n = Nummer[i] - '0';
        CheckEl[n] = CheckEl[n] + 1;
        if (CheckEl[n] > 1)
            return -1;
    }
    return 0;
}

int CheckSymbols(char * Nummer, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if ((Nummer[i] < '0') || ('9' < Nummer[i]))
            return -1;
    }
    for (int i = 0; i < size - 1; ++i)
    {
        if (Nummer[i] != Nummer[i+1])
            return 0;
    }
    return -1;
}

int CheckBadInput(char * Nummer, int size)
{
    if ((CheckSymbols(Nummer, size) == -1) || (CheckElements(Nummer, size) == -1))
        return -1;
    return 0;
}

void Permutation(char * Nummer, int size, int NumOfPerm)
{
    for (int i = 0; i < NumOfPerm; ++i)
    {
        if (CheckOrder(Nummer, size) == -1)
            break;
        int IndexMaxEl = FindMaxIndex(Nummer, size);
        int IndexBiggerEl = FindBiggerElement(Nummer, size, IndexMaxEl);
        swap(&Nummer[IndexMaxEl], &Nummer[IndexBiggerEl] );
		reverse(Nummer + IndexMaxEl + 1, size-IndexMaxEl-1);
        printf("%s", Nummer);
    }
}
int main()
{
    char Nummer[100];
    if (fgets(Nummer, 100, stdin) == 0)
        return 0;
    const int size = strlen(Nummer) - 1;
    int NumOfPerm;

    if (scanf("%d", &NumOfPerm) != 1)
        return 0;

    if ((size == 1) || (NumOfPerm == 0))
    {
        printf("\n");
        return 0;
    }

    if (CheckBadInput(Nummer, size) == -1)
    {
        printf("bad input\n");
        return 0;
    }
    if (CheckOrder(Nummer, size) == -1)
    {
        printf("\n");
        return 0;
    }
    Permutation(Nummer, size, NumOfPerm);
}
