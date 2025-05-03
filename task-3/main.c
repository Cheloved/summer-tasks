#include <stdio.h>
#include <string.h>

int print_help()
{
    return 0;
}

int main(int argc, char** argv)
{
    if ( argc != 4 )
    {
        print_help();
        return -1;
    }

}
