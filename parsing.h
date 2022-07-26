#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "./libft/libft.h"

char	**read_map(int fd);
void    parsing(char *map);

#endif