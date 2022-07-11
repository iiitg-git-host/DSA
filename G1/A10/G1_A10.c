#include <stdio.h>
#include <stdlib.h>

void input_array(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Enter element at index %d :", i);
        scanf("%d", &array[i]);
    }
}
void int_swap(int array[], int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}
void print(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
}

void min_heapify_up(int array[], int size, int idx)
{
    if (idx)
    {
        int parent;
        if (idx % 2 == 0)
        {
            parent = (idx - 2) / 2;
        }
        else
        {
            parent = (idx - 1) / 2;
        }
        if (array[parent] > array[idx])
        {
            int_swap(array, idx, parent);
            min_heapify_up(array, size, parent);
        }
    }
}
void min_heapify_down(int array[], int size, int idx)
{

    int minimum = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && array[left] < array[minimum])
    {
        minimum = left;
    }
    if (right < size && array[right] < array[minimum])
    {
        minimum = right;
    }
    if (minimum != idx)
    {
        int_swap(array, minimum, idx);
        min_heapify_down(array, size, idx);
    }
}

int extract_min(int min_heap[], int *min_heap_size)
{
    if (*min_heap_size == 0)
    {
        return -1;
    }
    if (*min_heap_size == 1)
    {
        return min_heap[0];
    }
    int min = min_heap[0];
    min_heap[0] = min_heap[--(*min_heap_size)];
    min_heapify_down(min_heap, (*min_heap_size), 0);
    return min;
}

void build_min_heap(int array[], int size)
{
    int init = (size / 2) - 1;
    for (int i = init; i >= 0; i--)
    {
        min_heapify_down(array, size, i);
    }
}
void get_n_smallest_pairs(int A[], int *size_A, int B[], int *size_B, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n%d :[%d %d]", i + 1, extract_min(A, size_A), extract_min(B, size_B));
        printf("\nA:");
        print(A, *size_A);
        printf("\nB:");
        print(B, *size_B);
    }
}

int main()
{
    int size_A, size_B, n;
    printf("\nEnter sizes of array A and array B: ");
    scanf("%d %d", &size_A, &size_B);
    int A[size_A], B[size_B];
    printf("\nA:");
    input_array(A, size_A);
    printf("\nB:");
    input_array(B, size_B);
    build_min_heap(A, size_A);
    build_min_heap(B, size_B);
    printf("\nEnter value of n: ");
    scanf("%d", &n);
    get_n_smallest_pairs(A, &size_A, B, &size_B, n);
}

// 6 
// 6
// 4 6 1 2 5 3
// 10 12 14 13 11 9
//6 6 4 6 1 2 5 3 10 12 14 13 11 9