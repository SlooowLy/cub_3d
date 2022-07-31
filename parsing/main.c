#include "parsing.h"

void print_data(data *d)
{
	printf("%s\n", d->n_path);
	printf("%s\n", d->s_path);
	printf("%s\n", d->e_path);
	printf("%s\n", d->w_path);
	printf("%lX\n", d->c_hexa);
	printf("%lX\n", d->f_hexa);
    if (d->map == 0)
        printf("0\n");
    for (int i = 0; d->map[i]; i++)
        printf("%s\n", d->map[i]);
}

void    free_stack(data *d)
{
    free(d->n_path);
    free(d->s_path);
    free(d->e_path);
    free(d->w_path);
    free_arr(d->map);
    free(d);
}

int main(int ac, char **av)
{
    data  *d;
    if (ac != 2)
        return 1;
    d = parsing(av[1]);
    print_data(d);
    free_stack(d);
    // system("leaks parsing");
}