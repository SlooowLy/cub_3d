#include "cub_3d.h"

void raydraw(int xA,int yA,int xB,int yB,t_info *game)
{
	// yB = yA+3;
	// xB = xA+3;
	//find_endline(&xB,&yB,game);
	// yB *= 3;
	// xB *= 3;
	int dx = xB - xA;
	int dy = yB - yA;

	float step = fmaxf(abs(dx),abs(dy));
	float xinc = dx/step;
	float yinc = dy/step;

	float x = xA,y = yA;

	while (step >= 0)
	{
		// printf ("x = %f, x/15 %d, y = %d\n", x)
		// printf ("x>>>%f, y>>>%f\n", x, y);
		// printf ("x***%d, y***%d\n", (int)floor(x), (int)floor(y));
		if(game->map[(int)floor(y / 15)][(int)floor(x / 15)] == '1')
			break;
		mlx_pixel_put(game->ml,game->window,round(x),round(y),0x000000);
		// printf("%c\n", game->map[(int)x / 15][(int)y /15]);
		x += xinc;
		y += yinc;
		// if(game->map[(int)y][(int)x] == '1')
		// 	break ;
		step--;
	}
	// drawDDA(xA, yA,z (int)x, (int)y, game);
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

void	my_mlx_pixel_put(t_img *data, int i, int color)
{
	char	*dst;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (i == 1)
	{
		while (y != 480)
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
		while (y != 15)
		{
			x = 0;
			while (x != 15)
			{
				dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
				x++;
				*(unsigned int*)dst = color;
			}
			y++;
		}

	}
	else
	{
		while (y != 5)
		{
			x = 0;
			while (x != 5)
			{
				dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
				x++;
				*(unsigned int*)dst = color;
			}
			y++;
		}

	}
}

void	rander_view(t_info *info)
{
	double	npa;
	int		i;

	i = 120;
	npa = info->pa - (FOV / 2);
	while (i--)
	{
		raydraw(info->px, info->py, info->px + cos(npa) * ((12 * 15) + (8 * 15)), info->py + sin(npa) * ((12 * 15) + (8 * 15)), info);
		npa += FOV/120;
	}
}
int	draw(void *stru)
{
	t_info	*info;
	int		i;
	int		j;

	i = -1;
	info = stru;
	update_player_cord(info);
	while (info->map[++i])
	{
		j = -1;
		while (info->map[i][++j])
		{
			if (info->map[i][j] == '0')
				mlx_put_image_to_window(info->ml, info->window, info->img1.img, j * 15, i * 15);
			else if (info->map[i][j] == '1')
				mlx_put_image_to_window(info->ml, info->window, info->img2.img, j * 15, i * 15);
		}
	}
	mlx_put_image_to_window(info->ml, info->window, info->img3.img, info->px - 2, info->py - 2);
	rander_view(info);
	return (0);
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

void	creat_imgs(t_info *info)
{
	info->img1.img = mlx_new_image(info->ml, 852, 480);
	info->img2.img = mlx_new_image(info->ml, 15, 15);
	info->img3.img = mlx_new_image(info->ml, 5, 5);
	info->img1.addr = mlx_get_data_addr(info->img1.img, &info->img1.bits_per_pixel, &info->img1.line_length, &info->img1.endian);
	info->img2.addr = mlx_get_data_addr(info->img2.img, &info->img2.bits_per_pixel, &info->img2.line_length, &info->img2.endian);
	info->img3.addr = mlx_get_data_addr(info->img3.img, &info->img3.bits_per_pixel, &info->img3.line_length, &info->img3.endian);
	my_mlx_pixel_put(&info->img1, 1, 0x0000FFFF);
	my_mlx_pixel_put(&info->img2, 2, 0x00FF0000);
	my_mlx_pixel_put(&info->img3, 0, 0x00000000);
	mlx_put_image_to_window(info->ml, info->window, info->img1.img, 0, 0);
}

void	get_player_position(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (info->map[++i])
	{
		j = -1;
		while (info->map[i][++j])
		{
			if (info->map[i][j] == 'N')
			{
				info->px = j * 15;
				info->py = i * 15;
				return ;
			}
		}
	}
}

void	player_next_position(t_info *info, int i)
{
	int	x;
	int	y;

	if (i == 1)
	{
		x = round(info->px + (cos(info->pa)) * 3);
		y = round(info->py + (sin(info->pa)) * 3);
		if(info->map[(int)floor(y / 15)][(int)floor(x / 15)] != '1')
		{
			info->px = x;
			info->py = y;
		}
	}
	if (i == 2)
	{
		x = round(info->px + cos(info->pa) * -3);
		y = round(info->py + sin(info->pa) * -3);
		if(info->map[(int)floor(y / 15)][(int)floor(x / 15)] != '1')
		{
			info->px = x;
			info->py = y;
		}
	}
	if (i == 3)
	{
		x = round(info->px + sin(info->pa) * 3);
		y = round(info->py - cos(info->pa) * 3);
		if(info->map[(int)floor(y / 15)][(int)floor(x / 15)] != '1')
		{
			info->px = x;
			info->py = y;
		}
	}
	if (i == 4)
	{
		x = round(info->px - sin(info->pa) * 3);
		y = round(info->py + cos(info->pa) * 3);
		if(info->map[(int)floor(y / 15)][(int)floor(x / 15)] != '1')
		{
			info->px = x;
			info->py = y;
		}
	}
}

void	update_player_cord(t_info *info)
{
	if (info->up.k_w)
		player_next_position(info, 1);
	if (info->up.k_s)
		player_next_position(info, 2);
	if (info->up.k_a)
		player_next_position(info, 3);
	if (info->up.k_d)
		player_next_position(info, 4);
	if (info->up.k_right)
	{
		info->pa = info->pa + (5 * (PI / 150));
		if (info->pa > PI * 2)
			info->pa = info->pa - (2 * PI);
	}
	if (info->up.k_left)
	{
		info->pa = info->pa - (5 * (PI / 150));
		if (info->pa < 0)
			info->pa = info->pa + (2 * PI);
	}
}

int	key_press(int key, t_info *info)
{
	if (key == KEY_W)
		info->up.k_w = 1;
	if (key == KEY_S)
		info->up.k_s = 1;
	if (key == KEY_A)
		info->up.k_a = 1;
	if (key == KEY_D)
		info->up.k_d = 1;
	if (key == KEY_RIGHT)
		info->up.k_right = 1;
	if (key == KEY_LEFT)
		info->up.k_left = 1;
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == KEY_W)
		info->up.k_w = 0;
	if (key == KEY_S)
		info->up.k_s = 0;
	if (key == KEY_A)
		info->up.k_a = 0;
	if (key == KEY_D)
		info->up.k_d = 0;
	if (key == KEY_RIGHT)
		info->up.k_right = 0;
	if (key == KEY_LEFT)
		info->up.k_left = 0;
	return (0);
}

void	ft_creat_window(t_info *info)
{
	info->ml = mlx_init();
	info->window = mlx_new_window(info->ml, 852, 480, "CUB_3D");
	creat_imgs(info);
	get_player_position(info);
	mlx_loop_hook(info->ml, draw, info);
	mlx_hook(info->window, 2, 1L<<0, key_press, info);
	mlx_hook(info->window, 3, 1L<<1, key_release, info);
	mlx_loop(info->ml);
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

int	main(int ac, char **av)
{
	t_info	info;
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
	ft_creat_window(&info);
	return (0);
}
