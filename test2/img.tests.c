#include "cub_3d.h"

# define PATH1 "./bluestone.xpm"

void	my_mlx_pixel_put(t_info *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img2.addr + (y * data->img2.line_length + x * (data->img2.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	get_color(t_info *mlx, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * mlx->img1.line_length + x * 4;
	ptr = mlx->img1.addr + pixel;
	return ((((unsigned char)ptr[2]) << 16) + (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}

// void	read_img(t_info *info)
// {

// }

int	draw(void *struc)
{
	t_info	*info;
	info = struc;
	int		img_width;
	int		img_height;
	int	i = -1;
	int	j;
	int	k = 0;

	info->img1.img = mlx_xpm_file_to_image(info->ml, PATH1, &img_width, &img_height);
	info->img2.img = mlx_new_image(info->ml, 200, 200);
	info->img1.addr = mlx_get_data_addr(info->img1.img, &info->img1.bits_per_pixel, &info->img1.line_length, &info->img1.endian);
	info->img2.addr = mlx_get_data_addr(info->img2.img, &info->img2.bits_per_pixel, &info->img2.line_length, &info->img2.endian);
	mlx_put_image_to_window(info->ml, info->window, info->img1.img, -50, -50);
	int *buff;

	// buff = malloc(4 * img_height * img_width);
	// while (++i < img_height)
	// {
	// 	j = 0;
	// 	while (j < img_width)
	// 	{
	// 		buff[k] = get_color(info, j, i);
	// 		j++;
	// 		k++;
	// 	}
	// }
	// i = -1;
	// k = 0;
	// while (++i < img_height)
	// {
	// 	j = 0;
	// 	while (j < img_width)
	// 	{
	// 		my_mlx_pixel_put(info, j, i, buff[k]);
	// 		k++;
	// 		j++;
	// 	}
	// }
	// i = -1;
	// k = 0;
	// while (++i < img_height)
	// {
	// 	j = 0;
	// 	while (j < img_width)
	// 	{
	// 		my_mlx_pixel_put(info, j + 60, i, buff[k]);
	// 		k++;
	// 		j++;
	// 	}
	// }
	// printf ("%d %d\n", i, j);
	// mlx_put_image_to_window(info->ml, info->window, info->img2.img, 0, 0);
	return(0);
}

int main()
{
	t_info  info;

	info.ml = mlx_init();
	info.window = mlx_new_window(info.ml, 40, 40, "CUB_3D");
	mlx_loop_hook(info.ml, draw, &info);
	mlx_loop(info.ml);
}