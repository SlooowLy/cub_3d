#include "parsing.h"

void    parsing(char *map)
{
    int fd;

    fd = open(map, O_RDONLY);
    if (!fd)
        return;
    char **s = read_map(fd);
    for (int i = 0; s[i]; i++)
        printf("%s\n", s[i]);
}