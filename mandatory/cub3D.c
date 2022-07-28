#include "cub3D.h"

void	get_map_h_w(t_info *info)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = -1;
	while (info->map[++i])
	{
		j = 0;
		while (info->map[i][j])
			j++;
		if (j > k)
			k = j;
	}
	info->map_h = i;
	info->map_w = k;
}

void	my_mlx_pixel_put(t_img *data, int i, int color)
{
	char	*dst;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (i == 1)
	{
		while (y != 240)
		{
			x = 0;
			while (x != 852)
			{
				dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
				*(unsigned int*)dst = color;
				x++;
			}
			y++;
		}
	}
	else if (i == 2)
	{
		while (y != WALL_SIZE)
		{
			x = 0;
			while (x != WALL_SIZE)
			{
				dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
				x++;
				*(unsigned int*)dst = color;
			}
			y++;
		}

	}
}

void	creat_imgs(t_info *info)
{
	info->img_u.img = mlx_new_image(info->ml, WINDOW_W, WINDOW_H / 2);
	info->img_d.img = mlx_new_image(info->ml, WINDOW_W, WINDOW_H / 2);
	info->img1.img = mlx_new_image(info->ml, WALL_SIZE, WALL_SIZE);
	info->img2.img = mlx_new_image(info->ml, WALL_SIZE, WALL_SIZE);
	info->img_d.addr = mlx_get_data_addr(info->img_d.img, &info->img_d.bits_per_pixel, &info->img_d.line_length, &info->img_d.endian);
	info->img_u.addr = mlx_get_data_addr(info->img_u.img, &info->img_u.bits_per_pixel, &info->img_u.line_length, &info->img_u.endian);
	info->img1.addr = mlx_get_data_addr(info->img1.img, &info->img1.bits_per_pixel, &info->img1.line_length, &info->img1.endian);
	info->img2.addr = mlx_get_data_addr(info->img2.img, &info->img2.bits_per_pixel, &info->img2.line_length, &info->img2.endian);
	my_mlx_pixel_put(&info->img_d, 1, 0x00008000);
	my_mlx_pixel_put(&info->img_u, 1, 0x000FFFF);
	my_mlx_pixel_put(&info->img1, 2, 0x0000FFFF);
	my_mlx_pixel_put(&info->img2, 2, 0x00FF0000);
}

void	creat_the_game(t_info *info)
{
	info->ml = mlx_init();
	get_texture_buff(info);
	get_map_h_w(info);
	info->window = mlx_new_window(info->ml, WINDOW_W, WINDOW_H, "cub_3D");
	creat_imgs(info);
	get_player_position(info);
	mlx_loop_hook(info->ml, draw, info);
	mlx_hook(info->window, 2, 1L<<0, key_press, info);
	mlx_hook(info->window, 3, 1L<<1, key_release, info);
	mlx_loop(info->ml);
}

char	*cpy(char *dest, char *src)
{
	int		i;
	char	*tmp;

	(void)dest;
	tmp = malloc (sizeof (char) * (ft_strlen(src) + 2));
	i = -1;
	while (src[++i])
		tmp[i] = src[i];
	tmp[i] = '\0';
	return (tmp);
}

void	get_default(t_info *info)
{
	info->pa = PI / 2;
	info->up.k_a = 0;
	info->up.k_d = 0;
	info->up.k_left = 0;
	info->up.k_right = 0;
	info->up.k_s = 0;
	info->up.k_w = 0;
}

char	**cpy_2(char **str, int j)
{
	int		i;
	int		k;
	char	**ret;

	i = -1;
	while (str[++i])
		i = i + 1 - 1;
	ret = malloc (sizeof (char *) * (i + 1));
	i = j - 2;
	k = -1;
	while (str[++i])
	{
		k++;
		ret[k] = cpy(ret[k], str[i]);
	}
	ret[k + 1] = NULL;
	return (ret);
}

int	get_map_info(t_info *info, char *map)
{
	int		i;
	char	**splited;

	i = -1;
	splited = ft_split(map, '\n');
	info->map = cpy_2(splited, 7);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;
	//tmp
	char	*map;
	int		fd;

	get_default(&info);
	if (ac != 2)
	{
		printf ("error\n");
		exit (1);
	}
	fd = open(av[1], O_RDONLY);
	read_map(&map, fd);
	if (!get_map_info(&info, map))
		return (0);
	fd = -1;
	while (info.map[++fd])
		printf ("%s\n", info.map[fd]);
	//tmp
	creat_the_game(&info);
	return (0);
}
