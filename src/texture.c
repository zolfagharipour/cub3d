/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:33:32 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/17 18:48:58 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	load_textures(t_common *d_list, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i++ < 19)
		mlx[i].ptr = mlx_init();
	open_texture(d_list, mlx);
	open_animation(mlx);
	i = 0;
	while (i++ < 19)
	{
		if (!mlx[i].texture)
			cleanup(d_list);
	}
	get_half_data(d_list, mlx);
	second_half_data(d_list, mlx);
	i = 0;
	while (i++ < 19)
	{
		if (!mlx[i].tex_data)
			cleanup(d_list);
	}
}

int	my_mlx_pixel_get(t_mlx *mlx, int x, int y)
{
	unsigned int	color;
	int				pos;

	if (x < 0 || x >= mlx->tex_d[0] || y < 0 || y >= mlx->tex_d[0])
		return (0);
	pos = (y * mlx->line_length + x * (mlx->bpp / 8));
	color = *(unsigned int *)(pos + mlx->tex_data);
	return (color);
}
