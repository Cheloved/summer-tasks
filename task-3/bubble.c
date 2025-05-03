#include "bubble.h"

int bubble_sort(char* input, long* array, long length, long* result)
{
    for ( int i = 0; i < length; i++ )
        result[i] = array[i];

    for ( int i = 0; i < length; i++ )
    {
        for ( int j = 0; j < length - i - 1; j++ )
        {
            if ( linecmp(input, result[j], result[j+1]) >= 0 ) 
            {
                int buf = result[j];
                result[j] = result[j+1];
                result[j+1] = buf;
            }
        }
    }

    return 0;
}
