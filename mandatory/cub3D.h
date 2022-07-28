#ifndef CUB_3D_H
# define CUB_3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# define WINDOW_H 480
# define WINDOW_W 852
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
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define NO "./texturse/greystone.xpm"
# define SO "./texturse/wood.xpm"
# define EA "./texturse/redbrick.xpm"
# define WE "./texturse/bluestone.xpm"
# define WALL_SIZE 64

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
	float	rayAngle;
	int		washitvertical;
	float	distance;
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
	int			window_h;
	int			window_w;
	int			map_h;
	int			map_w;
	t_calculations	rays[490];
	t_update	up;
	float		pa;
	float		px;
	float		py;
	t_img		img_u;
	t_img		img_d;
	t_img		img1;
	t_img		img2;
	void		*ml;
	void		*window;
	char    	**m_info;
	char    	**map;
	int			*buff_no;
	int			*buff_so;
	int			*buff_we;
	int			*buff_ea;
}   t_info;

int				draw(void *stru);
void			get_texture_buff(t_info *info);
void			get_no_texture(t_info *info);
void			get_we_texture(t_info *info);
void			get_so_texture(t_info *info);
unsigned int	get_color(t_img img, int x, int y);
void			get_player_position(t_info *info);
int				key_release(int key, t_info *info);
int				key_press(int key, t_info *info);
void			update_player_cord(t_info *info);
int				ft_strlen(char *c);
char			**cpy_2(char **str, int i);
char			**ft_split(char const *x, char c);
int				read_map(char **all, int fd);
void			update_player_cord(t_info *info);

#endif