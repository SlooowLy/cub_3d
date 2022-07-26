#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
#include <string.h>
# include <fcntl.h>
#include <errno.h>
# include "./libft/libft.h"

typedef struct 
{
	char			*n_path;
	char			*s_path;
	char			*w_path;
	char			*e_path;
	unsigned long	f_hexa;
	unsigned long	c_hexa;
	char			**map;
};


char	**read_map(int fd);
void    parsing(char *map);
void	print_error(int error);

#endif