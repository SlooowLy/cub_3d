#include "cub_3d.h"

///////////////////////////////////////


int		is_end_window(t_info *m, double x, double y)
{
	(void) m;
	if (x < 0 || x >= 8 * 15 ||
		y < 0 || y >= 8 * 15)
		return (TRUE);
	return (FALSE);
}
int		is_wall(t_info *m, int x, int y, char identf)
{
	int	grid_x;
	int	grid_y;

	if (is_end_window(m, x, y))
		return (TRUE);
	grid_x = floor(x / 15);
	grid_y = floor(y / 15);
	if (grid_x >= 8 || grid_y >= 8)
		return (TRUE);
	if (m->map[grid_y][grid_x] == identf)
		return (TRUE);
	return (FALSE);
}

int			ray_facing(double angle, int way)
{
	int	up;
	int	down;
	int	left;
	int	right;

	down = (angle > 0 && angle < PI) ? TRUE : FALSE;
	up = !(down) ? TRUE : FALSE;
	left = (angle > PI / 2 && angle < 3 * PI / 2) ? TRUE : FALSE;
	right = !left ? TRUE : FALSE;
	if (way == ray_up)
		return (up);
	else if (way == ray_down)
		return (down);
	else if (way == ray_left)
		return (left);
	else if (way == ray_right)
		return (right);
	return (-1);
}
void DrawCircle(int x, int y, int r,t_info *m)
{
      //static const double PI = 3.1415926535;
      double i, angle, x1, y1;

      for(i = 0; i < 360; i += 0.1)
      {
            angle = i;
            x1 = r * cos(angle * PI / 180);
            y1 = r * sin(angle * PI / 180);
            mlx_pixel_put(m->ml,m->window,x + x1, y + y1, 0xff3300);
      }
}
void draw_square(t_info *game)
{
     int    i = 0;
     int    j = 0;
 
    while(i < 4)
    {
        j = 0;
        while(j < 4)
        {
            mlx_pixel_put(game->ml, game->window, game->px*15 + i, game->py*15+j, 0xff0000);
            j++;
        }
        i++;
    }
}
void drawDDA(int xA,int yA,int xB,int yB,t_info *game)
{

	int dx = xB - xA;
	int dy = yB - yA;

	float step = fmaxf(abs(dx),abs(dy));
	float xinc = dx/step;
	float yinc = dy/step;

	float x = xA,y = yA;

	while (step >= 0)
	{
		// if(game->map[(int)y/10][(int)x/10] == '1')
		// 	break;
		mlx_pixel_put(game->ml,game->window,round(x),round(y),0xff3300);
		x += xinc;
		y += yinc;

		step--;
	}	
}
float normaliseangle(float angle)
{
	angle = remainder(angle ,(2*PI));
	if(angle < 0)
	{
		angle = (2*PI) + angle;
	}
	return (angle);
}
void cast_ray(float rayangel,int i,t_info *m)
{
	(void) i;
	// m->rays[i].rayAngle = rayangel;
	//rayangel = normaliseangle(rayangel);
	int wallhitx;
	int wallhity;
	// int rayisup;
	// int rayisdown;
	// int rayisleft;
	// int rayisright;
	float distance;
	float ystep;
	float xstep; 
	float yintercept;
	float xintercept;
	float rx;
	float ry;
	// rayisdown = 0;
	// rayisright = 0;
	wallhitx = 0;
	wallhity =0;
	distance = 0;
	// if(rayangel  > 0 && rayangel < PI)
	// 	rayisdown = 1;
	// rayisup = !rayisdown;
	// if(rayangel < 0.5 * PI || rayangel > 1.5 * PI)
	// 	rayisright = 1;
	// rayisleft = !rayisright;
	//drawDDA(m->pplayer->x*15,m->pplayer->y*15,m->pplayer->x*15+cos(rayangel)*30,m->pplayer->y*15+sin(rayangel)*30,m);
	////////////////////////////////////////////
	//////HORIZONTAL RAY !//////////////////////
	////////////////////////////////////////////
	
	yintercept = floor(m->py/15 )* 15;
	yintercept += ray_facing(rayangel, ray_down) ? 15 : 0;
	xintercept =  m->px + (yintercept - m->py) / tan(rayangel);
	 /////////////////////////////////////////
	// int j = 15;
	ystep = 15;
	ystep *=ray_facing(rayangel, ray_up) ? -1 : 1;
	
	xstep = 15/tan(rayangel);
	xstep *= (ray_facing(rayangel, ray_left) && xstep > 0) ? -1 : 1;
	xstep *= (ray_facing(rayangel, ray_right) && xstep < 0) ? -1 : 1;
	rx = xintercept;
	ry = yintercept;
	// float x;
	// float y;
	// if(rayisup)
	// 	ry--;
	// puts("ff");
	// while(j--)
	// {
	// 	x = rx;
	// 	y = ry;
	// 	rx += xstep;
	// 	ry += ystep;
	// }
	// puts("ffg");
	float	x_chk;
	float	y_chk;

	x_chk = xintercept;
	y_chk = yintercept;
	// if(ray_facing(rayangel, ray_up))
	// 	y_chk--;
	// (coord == HORZ) ?
	// 	horz_inter(vars, next, ray_angle, &step) :
	// 	vert_inter(vars, next, ray_angle, &step);
	puts("ff");
	while (!is_end_window(m, x_chk, y_chk))
	{
		x_chk = xintercept + ((ray_facing(rayangel, ray_left)&& 0) ? -1 : 0);
		x_chk += ((ray_facing(rayangel, ray_right) && 0) ? 1 : 0);
		y_chk = yintercept + ((ray_facing(rayangel, ray_down)&& 1) ? 1 : 0);
		y_chk += ((ray_facing(rayangel, ray_up)&&1) ? -1 : 0);
		//x_chk = xintercept;
		//y_chk = yintercept;
		if (is_wall(m, x_chk, y_chk, '1'))
		{
			drawDDA(m->px,m->py,xintercept,yintercept,m);
			puts("hit");
			break ;
		}
		else
		{
			xintercept += xstep;
			yintercept += ystep;
		}
	}
	puts("gg");
	//printf("%d\n",rayisright);
}
void rays(t_info *m)
{
	int colum;
	colum = 0;
	float ra;
	ra = m->pa - (FOV/2);
	int i;
	i = 0;
	while(i < 1)
	{
		cast_ray(ra,i,m);
		i++;
		ra += FOV/480;
		colum++;
	}
	// 	i = 0;
	// float plane = (360 / 2) / (tan(FOV_ANGLE / 2));
	// while (i < 1)
	// {
	// 	ra = m->pplayer->rotatangle +
	// 		atan2(i - NUM_RAYS / 2, plane);
	// 	//ra = ft_normalize_angle(vars->ray[i]->ray_angle);
	// 	//check_closest_wall(vars, vars->ray[i], vars->ray[i]->ray_angle);
	// 	cast_ray(ra,i,m);
	// 	i++;
	// }
}



/////////////////////////////////



void raydraw(int xA,int yA,int xB,int yB,t_info *game, int i, double npa)
{
	int dx = xB - xA;
	int dy = yB - yA;
	t_win	brr;

	float step = fmaxf(abs(dx),abs(dy));
	float xinc = dx/step;
	float yinc = dy/step;

	float x = xA,y = yA;

	while (step >= 0)
	{
		if(game->map[(int)floor(y / 15)][(int)floor(x / 15)] == '1')
		{
			game->rays[i].w_x = (int)(x);
			game->rays[i].w_y = (int)(y);
			if (sin(npa) > 0.1 | sin(npa) < -0.1)
			{
				// printf ("%f\n", sin(npa));
				game->rays[i].distance = fabs((y - game->py) / sin(npa));
			}
			else
				game->rays[i].distance = fabsf(x - game->px);
			// if (!(int)game->rays[i].distance && i)
			// 	game->rays[i].distance = game->rays[i - 1].distance;
			printf ("%d > distance > %f x > %d px > %d y > %d py > %d npa > %f\n", i, game->rays[i].distance, (int)x, game->px, (int)y, game->py, npa);
			break ;
		}
		brr.mlx = game->ml;
		brr.mlx_win = game->window;
		// bresenham(&brr, game->px, game->py, xB, xA, 0x000000);
		mlx_pixel_put(game->ml,game->window,round(x),round(y),0x000000);
		x += xinc;
		y += yinc;
		step--;
	}
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
		while (y != 1)
		{
			x = 0;
			while (x != 1)
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
	// npa = info->pa;
	npa = info->pa - (FOV / 2);
	while (i)
	{
		raydraw(info->px, info->py, info->px + cos(npa) * ((12 * 15) + (8 * 15)), info->py + sin(npa) * ((12 * 15) + (8 * 15)), info, 120 - i, npa);
		// printf ("%d distance >>%f\n", 120 - i, info->rays[120 - i].distance);
		npa += FOV/120;
		i--;
	}
	// printf ("the wall x >>%d\n the wall y >>%d\n", info->rays[0].w_x, info->rays[0].w_y);
	// printf ("distance >> %f\n", info->rays[0].distance);
}

void	put_wall(t_info *info, int wall_h, int i)
{
	t_img	img;
	char	*dst;
	int		y;
	int		x;

	(void) info;
	img.img = mlx_new_image(info->ml, 3, wall_h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	while (y != wall_h)
	{
		x = 0;
		while (x != 3)
		{
			dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
			*(unsigned int*)dst = 0xffffff;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->ml, info->window, img.img, i, (480 / 2) - (wall_h / 2));
	mlx_destroy_image(info->ml, img.img);
}

void	rander_walls(t_info *info)
{
	int	i = 0;
	double	projection_distance;
	double	wall_height;

	projection_distance = (480 / 2) / tan(60 / 2);
	while (i != 120)
	{
		if ((int)info->rays[i].distance)
		{
			wall_height = (15 / info->rays[i].distance) * projection_distance;
			// printf ("%d distance >>>>>> %f\n", i, info->rays[i].distance);
			// printf ("hieght >>>>>>>> %f\n", wall_height);
			put_wall(info, (int)fabs((wall_height * 10)), i * 3);
		}
		i++;
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
	mlx_put_image_to_window(info->ml, info->window, info->img1.img, 0, 0);
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
	mlx_put_image_to_window(info->ml, info->window, info->img3.img, info->px, info->py);
	rander_view(info);
	rander_walls(info);
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
	info->img3.img = mlx_new_image(info->ml, 1, 1);
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
		// info->pa = info->pa + 0.004;
		if (info->pa > PI * 2)
			info->pa = info->pa - (2 * PI);
	}
	if (info->up.k_left)
	{
		info->pa = info->pa - (5 * (PI / 150));
		// info->pa = info->pa - 0.0041;
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
