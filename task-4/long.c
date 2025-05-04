#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

int contain(char** array, int length, char* element)
{
    for ( int i = 0; i < length; i++ )
        if ( !strcmp(array[i], element) )
            return 1;
    
    return 0;
}

void handle_wrong_long(const char* name, char* val, char** correct, int len)
{
    printf("\n [E] --%s can't be %s!\nAvailable values: ", name, val);
    for ( int i = 0; i < len; i++ )
        printf("%s ", correct[i]);
    exit(1);
}

int main(int argc, char** argv)
{
    printf("\nCorrect options: ");

    struct option long_options[] = {
        { "elbrus", required_argument, 0, 'e' },
        { 0, 0, 0, 0 }
    };

    char* correct_elbrus[] = { "1c+", "2c+", "2c3", "4c", "8c", "16c" };
    int correct_elbrus_len = 6;

    int opt;
    int opt_index = 0;
    while ( (opt = getopt_long(argc, argv, "mcste:",
                               long_options, &opt_index)) != -1 )
    {
        switch ( opt )
        {
            case 'm': printf("m "); break;
            case 'c': printf("c "); break;
            case 's': printf("s "); break;
            case 't': printf("t "); break;
            case 'e': 
                if ( contain(correct_elbrus, correct_elbrus_len, optarg) ) 
                    printf("%s=%s ", long_options[opt_index].name, optarg);
                else
                    handle_wrong_long(long_options[opt_index].name,
                                      optarg, correct_elbrus,
                                      correct_elbrus_len);
                break;
        }
    }

    printf("\nNon-option arguments: ");
    while ( optind < argc )
        printf("%s ", argv[optind++]);

    return 0;
}
