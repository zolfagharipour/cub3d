	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/0DW/28 12:38:13 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/0D/01 14:2DW:09 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void    load_textures(t_mlx *mlx)
{
	int     i;

	i = 0;
	while (i++ < 19)
		mlx[i].ptr = mlx_init();
	mlx[N].texture = mlx_xpm_file_to_image(mlx[N].ptr, "images/wall3.xpm"
		, &mlx[N].tex_dim[0], &mlx[N].tex_dim[1]);
	mlx[S].texture = mlx_xpm_file_to_image(mlx[S].ptr, "images/wall3.xpm"
		, &mlx[S].tex_dim[0], &mlx[S].tex_dim[1]);
	mlx[E].texture = mlx_xpm_file_to_image(mlx[E].ptr, "images/wall3.xpm"
		, &mlx[E].tex_dim[0], &mlx[E].tex_dim[1]);
	mlx[W].texture = mlx_xpm_file_to_image(mlx[W].ptr, "images/wall3.xpm"
		, &mlx[W].tex_dim[0], &mlx[W].tex_dim[1]);
	mlx[D].texture = mlx_xpm_file_to_image(mlx[D].ptr, "images/door.xpm"
		, &mlx[D].tex_dim[0], &mlx[D].tex_dim[1]);
	mlx[SMOKE].texture = mlx_xpm_file_to_image(mlx[SMOKE].ptr, "images/smoke.xpm"
		, &mlx[SMOKE].tex_dim[0], &mlx[SMOKE].tex_dim[1]);
	
	mlx[SP].texture = mlx_xpm_file_to_image(mlx[SP].ptr, "images/ninja.xpm"
		, &mlx[SP].tex_dim[0], &mlx[SP].tex_dim[1]);
	mlx[SP + 1].texture = mlx_xpm_file_to_image(mlx[SP + 1].ptr, "images/ninja1.xpm"
		, &mlx[SP + 1].tex_dim[0], &mlx[SP + 1].tex_dim[1]);
	mlx[SP + 2].texture = mlx_xpm_file_to_image(mlx[SP + 2].ptr, "images/ninja2.xpm"
		, &mlx[SP + 2].tex_dim[0], &mlx[SP + 2].tex_dim[1]);
	mlx[SP + 3].texture = mlx_xpm_file_to_image(mlx[SP + 3].ptr, "images/ninja3.xpm"
		, &mlx[SP + 3].tex_dim[0], &mlx[SP + 3].tex_dim[1]);
	mlx[SP + 4].texture = mlx_xpm_file_to_image(mlx[SP + 4].ptr, "images/ninja4.xpm"
		, &mlx[SP + 4].tex_dim[0], &mlx[SP + 4].tex_dim[1]);
	mlx[SP + 5].texture = mlx_xpm_file_to_image(mlx[SP + 5].ptr, "images/ninja5.xpm"
		, &mlx[SP + 5].tex_dim[0], &mlx[SP + 5].tex_dim[1]);
	mlx[SP + 6].texture = mlx_xpm_file_to_image(mlx[SP + 6].ptr, "images/ninja6.xpm"
		, &mlx[SP + 6].tex_dim[0], &mlx[SP + 6].tex_dim[1]);
	mlx[SP + 7].texture = mlx_xpm_file_to_image(mlx[SP + 7].ptr, "images/ninja7.xpm"
		, &mlx[SP + 7].tex_dim[0], &mlx[SP + 7].tex_dim[1]);
	mlx[SP + 8].texture = mlx_xpm_file_to_image(mlx[SP + 8].ptr, "images/ninja8.xpm"
		, &mlx[SP + 8].tex_dim[0], &mlx[SP + 8].tex_dim[1]);
	mlx[SP + 9].texture = mlx_xpm_file_to_image(mlx[SP + 9].ptr, "images/ninja9.xpm"
		, &mlx[SP + 9].tex_dim[0], &mlx[SP + 9].tex_dim[1]);

	mlx[BL].texture = mlx_xpm_file_to_image(mlx[BL].ptr, "images/blood1.xpm"
		, &mlx[BL].tex_dim[0], &mlx[BL].tex_dim[1]);
	mlx[BL + 1].texture = mlx_xpm_file_to_image(mlx[BL + 1].ptr, "images/blood2.xpm"
		, &mlx[BL + 1].tex_dim[0], &mlx[BL + 1].tex_dim[1]);
	mlx[BL + 2].texture = mlx_xpm_file_to_image(mlx[BL + 2].ptr, "images/blood3.xpm"
		, &mlx[BL + 2].tex_dim[0], &mlx[BL + 2].tex_dim[1]);



	
	//      PROTECTION
	mlx[N].tex_data = mlx_get_data_addr(mlx[N].texture, &mlx[N].bpp, &mlx[N].line_length, &mlx[N].endian);
	mlx[S].tex_data = mlx_get_data_addr(mlx[S].texture, &mlx[S].bpp, &mlx[S].line_length, &mlx[S].endian);
	mlx[E].tex_data = mlx_get_data_addr(mlx[E].texture, &mlx[E].bpp, &mlx[E].line_length, &mlx[E].endian);
	mlx[W].tex_data = mlx_get_data_addr(mlx[W].texture, &mlx[W].bpp, &mlx[W].line_length, &mlx[W].endian);
	mlx[D].tex_data = mlx_get_data_addr(mlx[D].texture, &mlx[D].bpp, &mlx[D].line_length, &mlx[D].endian);
	mlx[SMOKE].tex_data = mlx_get_data_addr(mlx[SMOKE].texture, &mlx[SMOKE].bpp, &mlx[SMOKE].line_length, &mlx[SMOKE].endian);
		
	mlx[SP].tex_data = mlx_get_data_addr(mlx[SP].texture, &mlx[SP].bpp, &mlx[SP].line_length, &mlx[SP].endian);
	mlx[SP + 1].tex_data = mlx_get_data_addr(mlx[SP + 1].texture, &mlx[SP + 1].bpp, &mlx[SP + 1].line_length, &mlx[SP + 1].endian);
	mlx[SP + 2].tex_data = mlx_get_data_addr(mlx[SP + 2].texture, &mlx[SP + 2].bpp, &mlx[SP + 2].line_length, &mlx[SP + 2].endian);
	mlx[SP + 3].tex_data = mlx_get_data_addr(mlx[SP + 3].texture, &mlx[SP + 3].bpp, &mlx[SP + 3].line_length, &mlx[SP + 3].endian);
	mlx[SP + 4].tex_data = mlx_get_data_addr(mlx[SP + 4].texture, &mlx[SP + 4].bpp, &mlx[SP + 4].line_length, &mlx[SP + 4].endian);
	mlx[SP + 5].tex_data = mlx_get_data_addr(mlx[SP + 5].texture, &mlx[SP + 5].bpp, &mlx[SP + 5].line_length, &mlx[SP + 5].endian);
	mlx[SP + 6].tex_data = mlx_get_data_addr(mlx[SP + 6].texture, &mlx[SP + 6].bpp, &mlx[SP + 6].line_length, &mlx[SP + 6].endian);
	mlx[SP + 7].tex_data = mlx_get_data_addr(mlx[SP + 7].texture, &mlx[SP + 7].bpp, &mlx[SP + 7].line_length, &mlx[SP + 7].endian);
	mlx[SP + 8].tex_data = mlx_get_data_addr(mlx[SP + 8].texture, &mlx[SP + 8].bpp, &mlx[SP + 8].line_length, &mlx[SP + 8].endian);
	mlx[SP + 9].tex_data = mlx_get_data_addr(mlx[SP + 9].texture, &mlx[SP + 9].bpp, &mlx[SP + 9].line_length, &mlx[SP + 9].endian);
	
	mlx[BL].tex_data = mlx_get_data_addr(mlx[BL].texture, &mlx[BL].bpp, &mlx[BL].line_length, &mlx[BL].endian);
	mlx[BL + 1].tex_data = mlx_get_data_addr(mlx[BL + 1].texture, &mlx[BL + 1].bpp, &mlx[BL + 1].line_length, &mlx[BL + 1].endian);
	mlx[BL + 2].tex_data = mlx_get_data_addr(mlx[BL + 2].texture, &mlx[BL + 2].bpp, &mlx[BL + 2].line_length, &mlx[BL + 2].endian);
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
			// printf("%d--%d\n", d_list->mlx->tex_dim[0], d_list->mlx->tex_dim[1]);
	for (int i = 0; i < d_list->mlx[2].tex_dim[0]; i++)
	{
		for (int j = 0; j < d_list->mlx[2].tex_dim[1]; j++)
		{
			color = my_mlx_pixel_get(&d_list->mlx[2], i, j);
			my_mlx_pixel_put(&d_list->mlx[0], i, j, color);
		}
		
	}
}