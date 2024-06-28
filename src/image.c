/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:19 by fmarggra          #+#    #+#             */
/*   Updated: 2024/06/28 19:17:47 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	draw_image(t_common *d_list)
{
	draw_minimap(d_list);
	draw_player(d_list);
}

void	put_image(t_common *d_list, t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->ptr, mlx->img);
	if (mlx->img == NULL)
		cleanup(d_list);
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->line_length, &mlx->endian);
	if (mlx->addr == NULL)
		cleanup(d_list);
	caster(d_list);
	draw_walls(d_list);
	draw_image(d_list);
	// south(d_list);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);

}

void	move_window(int keycode, t_common *d_list)
{
	t_mlx	*mlx;
	double	px_move;

	mlx = d_list->mlx;
	px_move = 10;


	if (keycode == XK_w)
		move_player(d_list, d_list->rc->look);
	else if (keycode == XK_s)
		move_player(d_list, d_list->rc->look + 1.0);
	else if (keycode == XK_a)
		move_player(d_list, d_list->rc->look + 0.5);
	else if (keycode == XK_d)
		move_player(d_list, d_list->rc->look - 0.5);
	put_image(d_list, mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

