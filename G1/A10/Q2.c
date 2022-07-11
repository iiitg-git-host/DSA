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
int get_min(int array[], int size)
{
    int min = -1;
    for (int i = 0; i < size; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    return min;
}
int get_max(int array[], int size)
{
    int max = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}
void print(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
}
void print_hash_table(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("key:%d -> %d ", i+2,array[i]);
    }
}

int get_hash_table_size(int array[], int size)
{
    return get_max(array, size) - get_min(array, size)+1;
}
void init_hash_table(int hash_table[], int hash_table_size)
{
    for (int i = 0; i < hash_table_size; i++)
    {
        hash_table[i] = 0;
    }
}
void build_hash_table(int hash_table[], int hash_table_size, int array[], int size)
{
    int offset = get_min(array, size);
    // printf("\nminimum %d\n", offset);
    for (int i = 0; i < size; i++)
    {
        hash_table[array[i] - offset]++;
    }
}

int are_hash_tables_equal(int hash_table_A[], int hash_table_B[], int hash_table_size)
{
    for (int i = 0; i < hash_table_size; i++)
    {
        // printf("\n\n%d\n\n%d %d", i, hash_table_A[i], hash_table_B[i]);
        if (hash_table_A[i] != hash_table_B[i])
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int size_A, size_B;
    printf("\nEnter sizes of array A and array B: ");
    scanf("%d %d", &size_A, &size_B);
    if (size_A != size_B)
    {
        printf("\nFalse");
        exit(0);
    }
    int A[size_A], B[size_B];
    printf("\nA:");
    input_array(A, size_A);
    printf("\nB:");
    input_array(B, size_B);
    int hash_table_size = get_hash_table_size(A, size_A);
    int hash_table_A[hash_table_size], hash_table_B[hash_table_size];
    init_hash_table(hash_table_A, hash_table_size);
    build_hash_table(hash_table_A, hash_table_size, A, size_A);
    init_hash_table(hash_table_B, hash_table_size);
    build_hash_table(hash_table_B, hash_table_size, B, size_B);
    // printf("A:\n");
    // print_hash_table(hash_table_A, hash_table_size);
    // printf("B:\n");
    // print_hash_table(hash_table_B, hash_table_size);    
    if (are_hash_tables_equal(hash_table_A, hash_table_B, hash_table_size))
    {
        printf("\nTrue\n");
    }
    else
    {
        printf("\nFalse\n");
    }
}
// 7 7   2 5 6 8 10 2 2    2 5 5 8 10 5 6 