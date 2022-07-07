#include <stdio.h>
#include <stdlib.h>

void inputArray(char array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Enter data at index %d:\n", i);
        scanf(" %c", &array[i]);
    }
}
void swap(int array[], int swap, int with)
{
    int temp = array[swap];
    array[swap] = array[with];
    array[with] = temp;
}
void generateRandomArray(int array[], int init, int size, int upperLimit)
{
    for (int i = init; i < size; i++)
    {
        array[i] = rand() % upperLimit;
    }
}
void copyArray(int array1[], int array2[], int init, int size)
{
    for (int i = init; i < size; i++)
    {
        array2[i] = array1[i];
    }
}

int find(int array[], int lowerBound, int upperBound, int key)
{
    for (int i = lowerBound; i < upperBound; i++)
    {
        if (array[i] == key)
        {
            return i;
        }
    }
}
int min(char array[], int size)
{
    char minimum = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] < minimum)
        {
            minimum = array[i];
        }
    }
    return minimum;
}
int max(char array[], int size)
{
    char maximum = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] > maximum)
        {
            maximum = array[i];
        }
    }
    return maximum;
}

void insertionSort(int array[], int lowerBound, int upperBound, int *swapCount, int *compCount)
{
    for (int m = lowerBound + 1; m < upperBound; m++)
    {
        int j = m;
        int i = m - 1;
        while (i >= lowerBound && array[i] > array[j])
        {
            (*compCount)++;
            swap(array, i--, j--);
            (*swapCount)++;
        }
    }
}


int partition(int array[], int lowerBound, int upperBound, int *swapCount, int *compCount)
{
    int pivot = array[lowerBound];
    int left = lowerBound + 1;
    int right = upperBound;
    while (left < right)
    {
        while (array[right] > pivot)
        {
            (*compCount)++;
            right--;
        }
        while (array[left] <= pivot)
        {
            (*compCount)++;
            left++;
        }
        if (left < right)
        {
            (*swapCount)++;
            swap(array, left, right);
        }
    }
    (*swapCount)++;
    swap(array, lowerBound, right);
    return right;
}
void quickSort(int array[], int lowerBound, int upperBound, int *swapCount, int *compCount)
{
    if (lowerBound < upperBound)
    {
        int pivot = partition(array, lowerBound, upperBound, swapCount, compCount);
        quickSort(array, lowerBound, pivot - 1, swapCount, compCount);
        quickSort(array, pivot + 1, upperBound, swapCount, compCount);
    }
}

int modifiedPartition(int array[], int lowerBound, int upperBound, int *swapCount, int *compCount)
{
    int pivot = array[lowerBound];
    if (upperBound - lowerBound >= 50)
    {

        int left = lowerBound + 1;
        int right = upperBound;
        while (left < right)
        {
            while (array[right] > pivot)
            {
                (*compCount)++;
                right--;
            }
            while (array[left] <= pivot)
            {
                (*compCount)++;
                left++;
            }
            if (left < right)
            {
                (*swapCount)++;
                swap(array, left, right);
            }
        }
        (*swapCount)++;
        swap(array, lowerBound, right);
        return right;
    }
    else
    {
        insertionSort(array, lowerBound, upperBound, swapCount, compCount);
        return find(array, lowerBound, upperBound, pivot);
    }
}
void modifiedQuickSort(int array[], int lowerBound, int upperBound, int *swapCount, int *compCount)
{
    if (lowerBound < upperBound)
    {
        int pivot = modifiedPartition(array, lowerBound, upperBound, swapCount, compCount);
        modifiedQuickSort(array, lowerBound, pivot - 1, swapCount, compCount);
        modifiedQuickSort(array, pivot + 1, upperBound, swapCount, compCount);
    }
}

void countSort(char array[], int size)
{
    int minimum = min(array, size);
    int maximum = max(array, size);
    int hashSize = maximum - minimum + 1;
    int hash[hashSize];
    for (int i = 0; i < hashSize; i++)
    {
        hash[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {
        hash[array[i] - minimum]++;
    }
    int i = 0;
    for (int _ = 0; _ < hashSize; _++)
    {
        while (hash[_])
        {
            array[i++] = (char)(_ + minimum);
            hash[_]--;
        }
    }
}

int main()
{
    int A[1000], A2[1000], A3[1000], B[1010], B2[1010], B3[1010];
    int upperLimit;
    int quickSwapCount = 0, quickCompCount = 0, insertSwapCount = 0, insertCompCount = 0, quickSwapCount2 = 0, quickCompCount2 = 0, insertSwapCount2 = 0, insertCompCount2 = 0, modifiedSwapCount = 0, modifiedCompCount = 0, modifiedSwapCount2 = 0, modifiedCompCount2 = 0;
    printf("Enter Upper Limit!\n");
    scanf("%d", &upperLimit);
    generateRandomArray(A, 0, 1000, upperLimit);
    copyArray(A, A2, 0, 1000);
    copyArray(A, A3, 0, 1000);
    quickSort(A, 0, 999, &quickSwapCount, &quickCompCount);
    insertionSort(A2, 0, 1000, &insertSwapCount, &insertCompCount);
    copyArray(A, B, 0, 1000);
    generateRandomArray(B, 1000, 1010, upperLimit);
    copyArray(B, B2, 0, 1010);
    copyArray(B, B3, 0, 1010);
    quickSort(B, 0, 1010, &quickSwapCount2, &quickCompCount2);
    insertionSort(B2, 0, 1010, &insertSwapCount2, &insertCompCount2);
    modifiedQuickSort(A3,0,999,&modifiedSwapCount, &modifiedCompCount );
    modifiedQuickSort(B3,0,1009,&modifiedSwapCount2, &modifiedCompCount2 );
    printf("\n1. Quick Sort A: swap:%d comp:%d\n", quickSwapCount, quickCompCount);
    printf("\n1. Insertion Sort A: swap:%d comp:%d\n\n", insertSwapCount, insertCompCount);
    printf("\n2. Quick Sort B: swap:%d comp:%d\n", quickSwapCount2, quickCompCount2);
    printf("\n2. Insertion Sort B: swap:%d comp:%d\n\n", insertSwapCount2, insertCompCount2);
    printf("\n3. modified Sort A: swap:%d comp:%d\n", modifiedSwapCount, modifiedCompCount);
    printf("\n3. modified Sort B : swap:%d comp:%d\n\n", modifiedSwapCount2, modifiedCompCount2);

    int size;
    printf("Enter Size of Array\n");
    scanf("%d", &size);
    char C[size];
    inputArray(C, size);
    countSort(C, size);
    for (int i = 0; i < size; i++)
    {
        printf("%c ", C[i]);
    }
}