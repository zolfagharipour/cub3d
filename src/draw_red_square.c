#include "cubid.h"

int calc_color(int x, int y, t_common *d_list)
{
    if (d_list->map->minimap[x][y] == 0)
        return LBLUE;
    else if  (d_list->map->minimap[x][y] == 1)
        return DBLUE;
    else
        return 0x0000000;
}

void put_red_square(t_common *d_list)
{
    t_mlx   *mlx;

    mlx = d_list->mlx;
    int start_x = d_list->map->scale + mlx->shift_x;
    int start_y = d_list->map->scale + mlx->shift_y;


    for (int y = 0; y < d_list->map->raw_height * d_list->map->scale; y++)
    {
        for (int x = 0; x < d_list->map->raw_length * d_list->map->scale; x++)
        {
            my_mlx_pixel_put(mlx, x, y, calc_color(x, y, d_list));
        }
    }
    for (int y = 0; y < d_list->map->scale; y++)
    {
        for (int x = 0; x < d_list->map->scale; x++)
        {
            my_mlx_pixel_put(mlx, start_x + x, start_y + y, ORANGE);
        }
    }
    for (int i = 0; i < WIDTH; i++)
    { 
        my_mlx_pixel_put(mlx, d_list->rc->hit[i][0] * d_list->map->scale, d_list->rc->hit[i][1] * d_list->map->scale, RED);
        // printf("%f:\t%f\n",  d_list->rc->hit[i][0] * d_list->map->scale, d_list->rc->hit[i][1] * d_list->map->scale);
    }

}

// int	c_rgb(int r, int g, int b)
// {
// 	return (r << 16 | g << 8 | b);
// }

// void	mix_colors(t_list *mlx, int i, int color)
// {
// 	if (color == BLUE)
// 	{
// 		if (i == mlx->max_iter)
// 			mlx->col = c_rgb(1, 30, 60);
// 		else
// 			mlx->col = c_rgb((i * 1) % 255, (i * 2 + 10) % 255, (i * 5) % 255);
// 	}
// 	else if (color == RED)
// 	{
// 		if (i == mlx->max_iter)
// 			mlx->col = c_rgb(48, 1, 1);
// 		else
// 			mlx->col = c_rgb((i * 5 + 50) % 255, (i * 2) % 255, (i * 2) % 255);
// 	}
// 	else if (color == GREEN)
// 	{
// 		if (i == mlx->max_iter)
// 			mlx->col = c_rgb(1, 70, 20);
// 		else
// 			mlx->col = c_rgb((i * 1) % 255, (i * 5) % 255, (i * 2) % 255);
// 	}
// }
