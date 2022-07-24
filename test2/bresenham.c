#include "cub_3d.h"

void    my_mlx_pixel_put2(t_win *win, int x, int y, int color)
{
    char    *dst;

    dst = win->add + (y * win->ll + x * (win->bpp / 8));
    *(unsigned int *)dst = color & 0x00ffffff;
}

void    bresenham(t_win *win, int x0, int y0, int x1, int y1, int c)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int dp1 = dx + dy;
    int dp2 = 0;
    while (1)
    {
        if ((x0 > 0 && x0 < 1920)
            && (y0 > 0 && y0 < 1080))
            mlx_pixel_put(win->mlx, win->mlx_win, x0,
                y0, c);
        if (x0 == x1 && y0 == y1)
            break ;
        dp2 = 2 * dp1;
        if (dp2 >= dy)
        {
            if (x0 == x1)
                break ;
            dp1 += dy;
            x0 += sx;
        }
        if (dp2 <= dx)
        {
            if (y0 == y1)
                break ;
            dp1 += dx;
            y0 += sy;
        }
    }
}