#include "cub_3d.h"

///////////////////////////////////////

int	lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int		is_end_window(t_info *m, double x, double y)
{
	if (x < 0 || x >= (16 * 64) ||
		y < 0 || y >= lines(m->map) * 16)
		return (TRUE);
	return (FALSE);
}

int		is_wall(t_info *m, int x, int y, char identf)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)floor(x / 16);
	grid_y = (int)floor(y / 16);
	if (is_end_window(m, x, y))
	{
		return (TRUE);
	}
	// if (grid_x >= 63 || grid_y >= lines(m->map))
	// 	return (TRUE);
	if (m->map[grid_y][grid_x] == identf)
	{
		return (TRUE);
	}
	return (FALSE);
}

int			ray_facing(float angle, int way)
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
      //static const float PI = 3.1415926535;
      float i, angle, x1, y1;

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
            mlx_pixel_put(game->ml, game->window, game->px*16 + i, game->py*16+j, 0xff0000);
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
		// if(game->map[(int)y/16][(int)x/16] == '1')
		// 	break;
		// puts ("yoooo");
		mlx_pixel_put(game->ml,game->window,round(x),round(y),0xff3300);
		// puts ("koooo");
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

float distancebetwenpoint(float x1,float y1,float x2,float y2)
{
	return(sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));
}

void cast_ray(float rayangel,int i,t_info *m)
{
	m->rays[i].rayAngle = rayangel;
	m->rays[i].washitvertical = FALSE;
	rayangel = normaliseangle(rayangel);
	int wallhitx;
	int wallhity;
	int rayisup;
	int rayisdown;
	int rayisleft;
	int rayisright;
	float distance;
	float ystep;
	float xstep; 
	float yintercept;
	float xintercept;
	float hhitx;
	float hhity;
	int findhorzwall_hit;
	findhorzwall_hit = FALSE;
	rayisdown = 0;
	rayisright = 0;
	wallhitx = 0;
	wallhity =0;
	distance = 0;
	if(rayangel  > 0 && rayangel < PI)
		rayisdown = 1;
	rayisup = !rayisdown;
	if(rayangel < 0.5 * PI || rayangel > 1.5 * PI)
		rayisright = 1;
	rayisleft = !rayisright;
	//drawDDA(m->pplayer->x*16,m->pplayer->y*16,m->pplayer->x*16+cos(rayangel)*30,m->pplayer->y*16+sin(rayangel)*30,m);
	////////////////////////////////////////////
	//////HORIZONTAL RAY !//////////////////////
	////////////////////////////////////////////
	
	yintercept = floor(m->py/16) * 16;
	if(rayisdown)
		yintercept += 16;
	xintercept =  m->px + (yintercept - m->py) / tan(rayangel);
	 /////////////////////////////////////////
	ystep = 16;
	if(rayisup)
		ystep *= -1;
	xstep = 16/tan(rayangel);
	if(rayisleft && xstep > 0)
		xstep *= -1;
	if(rayisright && xstep < 0)
		xstep *= -1;
	float	x_chk;
	float	y_chk;

	x_chk = xintercept;
	y_chk = yintercept;

	if(rayisup)
		y_chk--;
	while (1)
	{
		if (is_wall(m, x_chk, y_chk, '1'))
		{
			hhitx = x_chk;
			hhity = y_chk;
			findhorzwall_hit = TRUE;
			//drawDDA(m->pplayer->x,m->pplayer->y,x_chk,y_chk,m);
			break ;
		}
		else
		{
			x_chk += xstep;
			y_chk += ystep;
		}
	}
	//////////////////////////////////////////////////
	////////////////VIRTICAL//////////////////////////
	//////////////////////////////////////////////////
	int findvir_wall;
	float vhitx;
	float vhity;
	
	findvir_wall = FALSE;

	
	xintercept = floor(m->px/16) * 16;
	if(rayisright)
		xintercept += 16;
		
	yintercept =  m->py + (xintercept - m->px) * tan(rayangel);
	 /////////////////////////////////////////
	xstep = 16;
	if(rayisleft)
		xstep *= -1;
	ystep = 16*tan(rayangel);
	if(rayisup && ystep > 0)
		ystep *= -1;
	if(rayisdown && ystep < 0)
		ystep *= -1;
	float	vx_chk;
	float	vy_chk;

	vx_chk = xintercept;
	vy_chk = yintercept;

	if(rayisleft)
		vx_chk--;
	while (1)
	{
		if (is_wall(m, vx_chk, vy_chk, '1'))
		{
			// printf ("x >> %f, y >> %f\n", vx_chk, vy_chk);
			vhitx = vx_chk;
			vhity = vy_chk;
			findvir_wall = TRUE;
			// drawDDA(m->px,m->py,vx_chk,vy_chk,m);
			break ;
		}
		else
		{
			vx_chk += xstep;
			vy_chk += ystep;
		}
	}
	// printf ("xchck %f, xvchc %f\n", x_chk, y_chk);
	////////////call distance///////////////////////////////
	double horz_dist;
	double vert_dist;
	if(findhorzwall_hit)
		horz_dist = distancebetwenpoint(m->px,m->py,x_chk,y_chk);
	else
		horz_dist = INT_MAX;
	if(findvir_wall)
		vert_dist = distancebetwenpoint(m->px,m->py,vx_chk,vy_chk);
	else
		vert_dist = INT_MAX;
	
	if(horz_dist <= vert_dist)
	{
		wallhitx = x_chk;
		wallhity = y_chk;
	}
	else
	{
		wallhitx = vx_chk;
		wallhity = vy_chk;
	}
	///drawDDA(m->pplayer->x,m->pplayer->y,wallhitx,wallhity,m);
	m->rays[i].w_x = wallhitx;
	m->rays[i].w_y = wallhity;
	if(horz_dist < vert_dist)
		m->rays[i].distance = horz_dist;
	else
		m->rays[i].distance = vert_dist;
		m->rays[i].washitvertical = (vert_dist < horz_dist);
}

void rays(t_info *m)
{
	float ra;
	ra = m->pa - (FOV/2);
	int i;
	i = 0;
	while(i < 320)
	{
		// puts ("yoooo");
		cast_ray(ra,i,m);
		// puts ("koooo");
		// printf("x >> %d y >> %d\n", m->rays[i].w_x, m->rays[i].w_y);
		// drawDDA(m->px,m->py,m->rays[i].w_x,m->rays[i].w_y,m);
		i++;
		ra += FOV/320;
	}
}



/////////////////////////////////



void raydraw(int xA,int yA,int xB,int yB,t_info *game, int i, float npa)
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
		if(game->map[(int)floor(y / 16)][(int)floor(x / 16)] == '1')
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
			// printf ("%d > distance > %f x > %d px > %d y > %d py > %d npa > %f\n", i, game->rays[i].distance, (int)x, game->px, (int)y, game->py, npa);
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
		while (y != 16)
		{
			x = 0;
			while (x != 16)
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
	float	npa;
	int		i;

	i = 320;
	// npa = info->pa;
	npa = info->pa - (FOV / 2);
	while (i)
	{
		raydraw(info->px, info->py, info->px + cos(npa) * ((12 * 16) + (8 * 16)), info->py + sin(npa) * ((12 * 16) + (8 * 16)), info, 320 - i, npa);
		// printf ("%d distance >>%f\n", 320 - i, info->rays[320 - i].distance);
		npa += FOV/320;
		i--;
	}
	// printf ("the wall x >>%d\n the wall y >>%d\n", info->rays[0].w_x, info->rays[0].w_y);
	// printf ("distance >> %f\n", info->rays[0].distance);
}

void	put_wall(t_info *m, int wall_h, int i, unsigned int c)
{
	t_img	img;
	char	*dst;
	int		y;
	int		x;
	img.img = mlx_new_image(m->ml, 3, wall_h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	while (y != wall_h)
	{
		x = 0;
		while (x != 3)
		{
			dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
			*(unsigned int*)dst = c;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(m->ml, m->window, img.img, i, (500 / 2) - (wall_h / 2));
	mlx_destroy_image(m->ml, img.img);
}

// void	put_wall(t_info *info, int wall_h, int i)
// {
// 	t_img	img;
// 	char	*dst;
// 	int		y;
// 	int		x;

// 	(void) info;
// 	img.img = mlx_new_image(info->ml, 3, wall_h);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 	y = 0;
// 	while (y != wall_h)
// 	{
// 		x = 0;
// 		while (x != 3)
// 		{
// 			dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
// 			*(unsigned int*)dst = 0xffffff;
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(info->ml, info->window, img.img, i, (480 / 2) - (wall_h / 2));
// 	mlx_destroy_image(info->ml, img.img);
// }

void	rander_walls(t_info *info)
{
	int	i = 0;
	float	projection_distance;
	float	wall_height;
	unsigned int	color;

	// c = 0x03bafc;
	// d = 0x0FFFF00;

	projection_distance = (480 / 2) / tan(60 / 2);
	while (i < 320)
	{
		if ((int)info->rays[i].distance)
		{
			if (info->rays[i].washitvertical)
				color = 0x0C0C0C0;
			else
				color = 0x0808080;
			wall_height = (16 / info->rays[i].distance) * projection_distance;
			// printf ("%d distance >>>>>> %f\n", i, info->rays[i].distance);
			// printf ("hieght >>>>>>>> %f\n", wall_height);
			put_wall(info, (int)fabs((wall_height * 10)), i * 3, color);
		}
		i++;
	}
}

void projectewall3d(t_info *m)
{
	int i;
	i = 0;
	float raydist;
	float wallstripheigth;
	float distanceprojplan ;
	unsigned int	color;

	color = 0x03bafc;
	distanceprojplan = (1080/2)/tan(FOV/2);
	while(i < 320)
	{
		raydist = m->rays[i].distance;
		wallstripheigth = (16/raydist)*distanceprojplan;
		put_wall(m, (int)fabs((wallstripheigth)), i * 3, color);
		i++;
	}
}

int	draw(void *stru)
{
	t_info	*info;
	int		i;
	int		j;

	j = 0;
	i = -1;
	info = stru;
	mlx_clear_window(info->ml, info->window);
	update_player_cord(info);
	mlx_put_image_to_window(info->ml, info->window, info->img_u.img, 0, 0);
	mlx_put_image_to_window(info->ml, info->window, info->img_d.img, 0, 240);
	// while (info->map[++i])
	// {
	// 	j = -1;
	// 	while (info->map[i][++j])
	// 	{
	// 		if (info->map[i][j] == '0' || info->map[i][j] == 'N')
	// 			mlx_put_image_to_window(info->ml, info->window, info->img1.img, j * 16, i * 16);
	// 		else if (info->map[i][j] == '1')
	// 			mlx_put_image_to_window(info->ml, info->window, info->img2.img, j * 16, i * 16);
	// 	}
	// }
	rays(info);
	// projectewall3d(info);
	// rander_view(info);
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
	info->img_u.img = mlx_new_image(info->ml, 856, 240);
	info->img_d.img = mlx_new_image(info->ml, 856, 240);
	info->img1.img = mlx_new_image(info->ml, 16, 16);
	info->img2.img = mlx_new_image(info->ml, 16, 16);
	info->img3.img = mlx_new_image(info->ml, 1, 1);
	info->img_d.addr = mlx_get_data_addr(info->img_d.img, &info->img_d.bits_per_pixel, &info->img_d.line_length, &info->img_d.endian);
	info->img_u.addr = mlx_get_data_addr(info->img_u.img, &info->img_u.bits_per_pixel, &info->img_u.line_length, &info->img_u.endian);
	info->img1.addr = mlx_get_data_addr(info->img1.img, &info->img1.bits_per_pixel, &info->img1.line_length, &info->img1.endian);
	info->img2.addr = mlx_get_data_addr(info->img2.img, &info->img2.bits_per_pixel, &info->img2.line_length, &info->img2.endian);
	info->img3.addr = mlx_get_data_addr(info->img3.img, &info->img3.bits_per_pixel, &info->img3.line_length, &info->img3.endian);
	my_mlx_pixel_put(&info->img_d, 1, 0x00008000);
	my_mlx_pixel_put(&info->img_u, 1, 0x000FFFF);
	my_mlx_pixel_put(&info->img1, 2, 0x0000FFFF);
	my_mlx_pixel_put(&info->img2, 2, 0x00FF0000);
	my_mlx_pixel_put(&info->img3, 0, 0x00000000);
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
				info->px = j * 16;
				info->py = i * 16;
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
		x = round(info->px + (cos(info->pa)));
		y = round(info->py + (sin(info->pa)));
		if(info->map[(int)floor(y / 16)][(int)floor(x / 16)] != '1')
		{
			info->px = x;
			info->py = y;
		}
	}
	if (i == 2)
	{
		x = round(info->px + cos(info->pa) * -3);
		y = round(info->py + sin(info->pa) * -3);
		if(info->map[(int)floor(y / 16)][(int)floor(x / 16)] != '1')
		{
			info->px = x;
			info->py = y;
		}
	}
	if (i == 3)
	{
		x = round(info->px + sin(info->pa) * 3);
		y = round(info->py - cos(info->pa) * 3);
		if(info->map[(int)floor(y / 16)][(int)floor(x / 16)] != '1')
		{
			info->px = x;
			info->py = y;
		}
	}
	if (i == 4)
	{
		x = round(info->px - sin(info->pa) * 3);
		y = round(info->py + cos(info->pa) * 3);
		if(info->map[(int)floor(y / 16)][(int)floor(x / 16)] != '1')
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
		// info->pa = info->pa + (5 * (PI / 150));
		info->pa = info->pa + 0.041;
		// if (info->pa > PI * 2)
		// 	info->pa = info->pa - (2 * PI);
	}
	if (info->up.k_left)
	{
		// info->pa = info->pa - (5 * (PI / 150));
		info->pa = info->pa - 0.041;
		// if (info->pa < 0)
		// 	info->pa = info->pa + (2 * PI);
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
