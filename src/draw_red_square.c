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
    double start_x = d_list->rc->pos[0] * d_list->map->scale - SQUARE / 2;
    double start_y = d_list->rc->pos[1] * d_list->map->scale - SQUARE / 2;

    for (int y = 0; y < d_list->map->raw_height * d_list->map->scale; y++)
    {
        for (int x = 0; x < d_list->map->raw_length * d_list->map->scale; x++)
        {
            my_mlx_pixel_put(mlx, x, y, calc_color(x, y, d_list));
        }
    }
    for (int y = 0; y < SQUARE; y++)
    {
        for (int x = 0; x < SQUARE; x++)
        {
            my_mlx_pixel_put(mlx, start_x + x, start_y + y, ORANGE);
        }
    }
    // for (int i = 0; i < WIDTH; i++)
    // {
    //     my_mlx_pixel_put(mlx, d_list->rc->hit[i][0] * d_list->map->scale, d_list->rc->hit[i][1] * d_list->map->scale, RED);
    //     double p1[2] = {d_list->rc->pos[0] * d_list->map->scale, d_list->rc->pos[1] * d_list->map->scale};
    //     double p2[2] = {d_list->rc->hit[i][0] * d_list->map->scale, d_list->rc->hit[i][1] * d_list->map->scale};
    // 	line(d_list, p1, p2, RED);
    // }
}



