#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    printf("Correct options: ");
    int opt;
    while ( (opt = getopt(argc, argv, "mcst")) != -1 )
    {
        switch ( opt )
        {
            case 'm': printf("m "); break;
            case 'c': printf("c "); break;
            case 's': printf("s "); break;
            case 't': printf("t "); break;
        }
    }

    printf("\nNon-option arguments: ");
    while ( optind < argc )
        printf("%s ", argv[optind++]);

    return 0;
}
