#include "parsing.h"

void    parse_line(char *str, char *str2)
{
	int i = 0;
	while(str2[i] == ' ')
		i++;
	str = strdup(str2 + i);
}