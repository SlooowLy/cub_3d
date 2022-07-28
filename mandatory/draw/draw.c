/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:17:53 by aaitoual          #+#    #+#             */
/*   Updated: 2022/07/28 10:14:37 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int		is_end_window(t_info *m, double x, double y)
{
	if (x < 0 || x >= (WALL_SIZE * WALL_SIZE) ||
		y < 0 || y >= m->map_h * WALL_SIZE)
		return (TRUE);
	return (FALSE);
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

int		is_wall(t_info *m, int x, int y, char identf)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)floor(x / WALL_SIZE);
	grid_y = (int)floor(y / WALL_SIZE);
	if (is_end_window(m, x, y))
	{
		return (TRUE);
	}
	if (m->map[grid_y][grid_x] == identf)
	{
		return (TRUE);
	}
	return (FALSE);
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
	
	yintercept = floor(m->py/WALL_SIZE) * WALL_SIZE;
	if(rayisdown)
		yintercept += WALL_SIZE;
	xintercept =  m->px + (yintercept - m->py) / tan(rayangel);
	 /////////////////////////////////////////
	ystep = WALL_SIZE;
	if(rayisup)
		ystep *= -1;
	xstep = WALL_SIZE/tan(rayangel);
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

	
	xintercept = floor(m->px/WALL_SIZE) * WALL_SIZE;
	if(rayisright)
		xintercept += WALL_SIZE;
		
	yintercept =  m->py + (xintercept - m->px) * tan(rayangel);
	 /////////////////////////////////////////
	xstep = WALL_SIZE;
	if(rayisleft)
		xstep *= -1;
	ystep = WALL_SIZE*tan(rayangel);
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

void rays(t_info *m)
{
	float ra;
	ra = m->pa - (FOV/2);
	int i;
	i = 0;
	while(i < 320)
	{
		// puts ("yoooo");
		cast_ray(ra, i, m);
		// puts ("koooo");
		// printf("x >> %d y >> %d\n", m->rays[i].w_x, m->rays[i].w_y);
		// drawDDA(m->px,m->py,m->rays[i].w_x,m->rays[i].w_y,m);
		i++;
		ra += FOV/320;
	}
}

void	put_wall(t_info *m, float wall_height, int i, unsigned int c)
{
	t_img	img;
	char	*dst;
	int		y;
	int		x;
	int		ix;
	int		iy;
	int		wall_h;
	// int		u;

	wall_h = (int)fabs((wall_height * 16));
	c = c+1;
	img.img = mlx_new_image(m->ml, 3, wall_h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	if (!m->rays[i / 3].washitvertical)
		ix = (int)((m->rays[i / 3].w_x) % WALL_SIZE);
	else
		ix = (int)((m->rays[i / 3].w_y) % WALL_SIZE);
	while (y != wall_h)
	{
		iy = (y) * ((WALL_SIZE / (float)wall_h));
		x = 0;
		while (x != 3)
		{
			dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
			*(unsigned int*)dst = m->buff_no[(WALL_SIZE *iy) + ix];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(m->ml, m->window, img.img, i, (480 / 2) - (wall_h / 2));
	mlx_destroy_image(m->ml, img.img);
}


void	rander_walls(t_info *info)
{
	int	i = 0;
	float	projection_distance;
	float	wall_height;
	unsigned int	color;
	float	dis;

	// c = 0x03bafc;
	// d = 0x0FFFF00;

	projection_distance = (852 / 2) / tan(60  / 2);
	while (i < 320)
	{
		if ((int)info->rays[i].distance)
		{
			if (info->rays[i].washitvertical)
				color = 0x0C0C0C0;
			else
				color = 0x0808080;
			dis = info->rays[i].distance * cos(info->rays[i].rayAngle - info->pa);
			wall_height = (WALL_SIZE / dis)  * projection_distance;
			// if (info->rays[i].w_x <= 32 && info->rays[i].w_y <= 32)
			put_wall(info, wall_height, i * 3, color);
		}
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
	// 			mlx_put_image_to_window(info->ml, info->window, info->img1.img, j * WALL_SIZE, i * WALL_SIZE);
	// 		else if (info->map[i][j] == '1')
	// 			mlx_put_image_to_window(info->ml, info->window, info->img2.img, j * WALL_SIZE, i * WALL_SIZE);
	// 	}
	// }
	rays(info);
	rander_walls(info);
	return (0);
}
