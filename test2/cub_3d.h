#ifndef CUB_3D_H
# define CUB_3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# define KEY_A 0
# define KEY_D 2
# define KEY_W 13
# define KEY_S 1
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define PI 3.141592653589793238
# define FOV 60 * (PI / 180)
# define TRUE 1
# define FALSE 0
// # include "./libft/libft.h"

///////////////////////
typedef enum	e_playerface
{
	ray_up,
	ray_down,
	ray_left,
	ray_right
}	t_playerface;
//////////////////////


typedef struct s_calculations
{
	int	w_x;
	int	w_y;
	double	distance;
}	t_calculations;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_win
{
    void    *mlx;
    void    *mlx_win;
    char    *add;
    int     bpp;
    int     ll;
	t_img	img;
}           t_win;

typedef struct	s_update
{
	int	k_d;
	int	k_a;
	int	k_s;
	int	k_w;
	int	k_left;
	int	k_right;
}	t_update;

typedef struct s_info
{
	t_calculations	rays[490];
	t_update	up;
	float		pa;
	int			px;
	int			py;
	t_img		img1;
	t_img		img2;
	t_img		img3;
	void		*ml;
	void		*window;
	char    	**m_info;
	char    	**map;
}   t_info;

void    bresenham(t_win *win, int x0, int y0, int x1, int y1, int c);
int		ft_strlen(char *c);
char	**cpy_2(char **str, int i);
char	**ft_split(char const *x, char c);
int		read_map(char **all, int fd);
void	update_player_cord(t_info *info);

#endif