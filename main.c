#include "parsing.h"

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    parsing(av[1]);
}