#include "cubid.h"

int	check_entire_square(t_common *d_list, int new_x, int new_y)
{
	double upper_left_x = new_x - SQUARE / 2;
    double upper_left_y = new_y - SQUARE / 2;

	for (int y = - 2; y < SQUARE + 2; y++)
    {
        for (int x = -1; x < SQUARE + 2; x++)
        {
			if  (d_list->map->minimap[(int)upper_left_x + x][(int)upper_left_y + y] == 1)
            	return TRUE;
        }
    }
	return FALSE;
}

double	calc_dir(double dir)
{
	double	rdir;
	if (dir >= 2)
		rdir -= 2;
	else if (dir < 0)
		rdir += 2;
	if (dir < 0.5)
		rdir = dir;
	else if (dir < 1.0)
		rdir = 1.0 - dir;
	else if (dir < 1.5)
		rdir = dir - 1;
	else if (dir < 2.0)
		rdir = 2 - dir;
	return (rdir);
}



int	move_check_x(t_common *d_list, double move_dir)
{
	double	trash;
	int		pos[2];

	pos[0] = d_list->rc->pos[0];
	pos[1] = d_list->rc->pos[1];

	if (cos(move_dir * M_PI) > 0 && d_list->map->raw_map[pos[0] + 1][pos[1]] == 1
		&& modf(d_list->rc->pos[0], &trash) > 0.6)
	{

		return (FALSE);
	}
	if (cos(move_dir * M_PI) < 0 && d_list->map->raw_map[pos[0] - 1][pos[1]] == 1
		&& modf(d_list->rc->pos[0], &trash) < 0.4)
	{
		return (FALSE);
	}
	return (TRUE);
}
int	move_check_y(t_common *d_list, double move_dir)
{
	double	trash;
	int		pos[2];

	pos[0] = d_list->rc->pos[0];
	pos[1] = d_list->rc->pos[1];

	if (sin(move_dir * M_PI) < 0 && (d_list->map->raw_map[pos[0]][pos[1] + 1] == 1 || d_list->map->raw_map[pos[0]][pos[1] + 1] == 4)
		&& modf(d_list->rc->pos[1], &trash) >= 0.6)
		return (FALSE);
	if (sin(move_dir * M_PI) > 0 && (d_list->map->raw_map[pos[0]][pos[1] - 1] == 1 || d_list->map->raw_map[pos[0]][pos[1] - 1] == 4)
		&& modf(d_list->rc->pos[1], &trash) <= 0.4)
		return (FALSE);
	return (TRUE);
}
void	move_player(t_common *d_list, double move_dir)
{
	if (move_check_x(d_list, move_dir))
		d_list->rc->pos[0] += cos (move_dir * M_PI) * (MOVING_DIS);
	if (move_check_y(d_list, move_dir))
		d_list->rc->pos[1] -= sin (move_dir* M_PI) * (MOVING_DIS);

}
void	rotate_player(int keycode, t_common *d_list)
{
	if (keycode == XK_Left)
		d_list->rc->look += 0.02;
	else if (keycode == XK_Right)
		d_list->rc->look -= 0.02;

	if (d_list->rc->look >= 2.0)
		d_list->rc->look -= 2.0;
	else if (d_list->rc->look < 0.0)
		d_list->rc->look += 2.0;
		// printf ("look %f\n", d_list->rc->look);
	put_image(d_list, d_list->mlx);
}