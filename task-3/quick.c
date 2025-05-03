#include "quick.h"

int quick_sort(char* input, long* array, long length, long* result)
{
    if ( array == NULL || length < 1 )
        return 0;

    if ( length == 1 )
    {
        result[0] = array[0];
        return 0;
    }

    long pivot = array[length / 2];

    long* left = (long*)calloc(length, sizeof(long));
    int left_length = 0;

    long* middle = (long*)calloc(length, sizeof(long));
    int middle_length = 0;

    long* right = (long*)calloc(length, sizeof(long));
    int right_length = 0;

    for ( long i = 0; i < length; i++ )
    {
        int cmp = linecmp(input, pivot, array[i]);
        if ( cmp < 0 )
            left[left_length++] = array[i];
        if ( cmp == 0 )
            middle[middle_length++] = array[i];
        if ( cmp > 0 )
            right[right_length++] = array[i];
    }

    if ( DEBUG )
    {
        printf(" >> Input: ");
        for ( int i = 0; i < length; i++ )
            printf("%ld ", array[i]);
        printf("\n >> Pivot: %ld\n", pivot);
        printf("\n >> Left: ");
        for ( int i = 0; i < left_length; i++ )
            printf("%ld ", left[i]);
        printf("\n >> Middle: ");
        for ( int i = 0; i < middle_length; i++ )
            printf("%ld ", middle[i]);
        printf("\n >> Right: ");
        for ( int i = 0; i < right_length; i++ )
            printf("%ld ", right[i]);
        printf("\n\n");
    }

    long* left_result   = (long*)malloc(sizeof(long) * left_length);
    if ( left_length > 1 )
    {
        quick_sort(input, left, left_length, left_result);
    } else {
        left_result[0] = left[0];
    }

    long* right_result   = (long*)malloc(sizeof(long) * right_length);
    if ( right_length > 1 )
    {
        quick_sort(input, right, right_length, right_result);
    } else {
        right_result[0] = right[0];
    }

    int current = 0;
    for ( int i = 0; i < right_length; i++ )
        result[current++] = right_result[i]; 
    for ( int i = 0; i < middle_length; i++ )
        result[current++] = middle[i]; 
    for ( int i = 0; i < left_length; i++ )
        result[current++] = left_result[i]; 

    free(left);
    free(middle);
    free(right);
    free(left_result);
    free(right_result);

    return 0;
}
