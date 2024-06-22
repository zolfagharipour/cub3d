#include "cubid.h"

int calc_color(int x, int y, t_common *d_list)
{
    if  (d_list->map->minimap[x][y] == 1)
        return DBLUE;
    else
        return LBLUE;
}

//print maze and player
void put_red_square(t_common *d_list)
{
    t_mlx   *mlx;

    mlx = d_list->mlx;
    int start_x = (d_list->map->player_x * d_list->map->scale) + mlx->shift_x;
    int start_y = (d_list->map->player_y * d_list->map->scale) + mlx->shift_y;

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
            my_mlx_pixel_put(mlx, start_x + x, start_y + y, RED);
        }
    }
}

void find_the_players_position(t_common *d_list)
{
    for (int i = 0; i < d_list->map->raw_height; i++)
    {
        for (int j = 0; j < d_list->map->raw_length; j++)
        {
            if (d_list->map->raw_map[i][j] == 2)
            {
                d_list->map->player_x = j;
                d_list->map->player_y = i;
                return ;
            }
        }
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
