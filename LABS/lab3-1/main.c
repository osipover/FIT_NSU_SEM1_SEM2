#include <stdio.h>
#include <stdlib.h>
void swap(int *p_left, int *p_right)
{
    int box = *p_left;
    *p_left = *p_right;
    *p_right = box;
}

void QuickSort(int *arr, int first, int last)
{
    if (first < last)
    {
        int left = first, right = last;
        int middle = arr[(left + right)/2];
        while (left < right)
        {
            while (arr[left] < middle)
                ++left;
            while (arr[right] > middle)
                --right;
            if (left <= right)
            {
                if (arr[left] > arr[right])
                    swap(&arr[left], &arr[right]);
                ++left;
                --right;
            }
        }
        QuickSort(arr, first, right);
        QuickSort(arr, left, last);
    }
}


int main() {
    int size;
    if (scanf("%d", &size) != 1)
        return 0;
    int *arr = malloc(size * sizeof(int));

    for (int i = 0; i < size; ++i)
        if(scanf("%d", &arr[i]) != 1)
            return 0;

    QuickSort(arr, 0, size - 1);

    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);

    free(arr);
    return 0;
}
