/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:38:13 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/01 13:32:04 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void    load_textures(t_mlx *mlx)
{
    int     i;

    i = 0;
    while (i++ < 5)
        mlx[i].ptr = mlx_init();
    mlx[1].texture = mlx_xpm_file_to_image(mlx[1].ptr, "images/knight.xpm"
        , &mlx[1].tex_dim[0], &mlx[1].tex_dim[1]);
    mlx[N].texture = mlx_xpm_file_to_image(mlx[N].ptr, "images/north.xpm"
        , &mlx[N].tex_dim[0], &mlx[N].tex_dim[1]);
    mlx[S].texture = mlx_xpm_file_to_image(mlx[S].ptr, "images/south.xpm"
        , &mlx[S].tex_dim[0], &mlx[S].tex_dim[1]);
    mlx[E].texture = mlx_xpm_file_to_image(mlx[E].ptr, "images/east.xpm"
        , &mlx[E].tex_dim[0], &mlx[E].tex_dim[1]);
    mlx[W].texture = mlx_xpm_file_to_image(mlx[W].ptr, "images/west.xpm"
        , &mlx[W].tex_dim[0], &mlx[W].tex_dim[1]);
 
    //      PROTECTION
    mlx[1].tex_data = mlx_get_data_addr(mlx[1].texture, &mlx[1].bpp, &mlx[1].line_length, &mlx[1].endian);
    mlx[N].tex_data = mlx_get_data_addr(mlx[N].texture, &mlx[N].bpp, &mlx[N].line_length, &mlx[N].endian);
    mlx[S].tex_data = mlx_get_data_addr(mlx[S].texture, &mlx[S].bpp, &mlx[S].line_length, &mlx[S].endian);
    mlx[E].tex_data = mlx_get_data_addr(mlx[E].texture, &mlx[E].bpp, &mlx[E].line_length, &mlx[E].endian);
    mlx[W].tex_data = mlx_get_data_addr(mlx[W].texture, &mlx[W].bpp, &mlx[W].line_length, &mlx[W].endian);
}
int my_mlx_pixel_get(t_mlx *mlx, int x, int y)
{
	unsigned int    color;
    int             pos;

	if (x < 0 || x >= mlx->tex_dim[0] || y < 0 || y >= mlx->tex_dim[0])
		return 0;
	pos = (y * mlx->line_length + x * (mlx->bpp / 8));
	color = *(unsigned int *)(pos + mlx->tex_data);
	
	return color;
}


void    south(t_common *d_list)
{
    int     color;

    load_textures(d_list->mlx);
            printf("%d--%d\n", d_list->mlx->tex_dim[0], d_list->mlx->tex_dim[1]);
    for (int i = 0; i < d_list->mlx[2].tex_dim[0]; i++)
    {
        for (int j = 0; j < d_list->mlx[2].tex_dim[1]; j++)
        {
            color = my_mlx_pixel_get(&d_list->mlx[2], i, j);
            my_mlx_pixel_put(&d_list->mlx[0], i, j, color);
        }
        
    }
}