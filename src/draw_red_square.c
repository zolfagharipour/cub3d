#include "cubid.h"

void put_red_square(t_mlx *mlx)
{
    int start_x = (WIDTH - W_SQUARE) / 2 + mlx->shift_x;
    int start_y = (HEIGHT - W_SQUARE) / 2 + mlx->shift_y;

    for (int y = 0; y < W_SQUARE; y++)
    {
        for (int x = 0; x < W_SQUARE; x++)
        {
            my_mlx_pixel_put(mlx, start_x + x, start_y + y, RED);
        }
    }
}

