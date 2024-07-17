#include "cubid.h"

int	fill_raw_map(t_common *d_list)
{
	char	*line;
	int		y;

	y = -1;
	d_list->map->fd = open(d_list->map->file, O_RDONLY);
	if (d_list->map->fd < 0)
		return (cleanup(d_list), 0);
	line = get_next_line(d_list->map->fd);
	while (++y < d_list->map->file_length - d_list->map->raw_height)
	{
		free(line);
		line = get_next_line(d_list->map->fd);
		if (!line)
			return (cleanup(d_list), 0);
	}
	y = -1;
	while (line && ++y < d_list->map->raw_height)
	{
		determine_content_of_coordinates(d_list, line, 0, y);
		line = get_next_line(d_list->map->fd);
		if (!line && y < d_list->map->raw_height - 1)
			cleanup(d_list);
	}
	close(d_list->map->fd);
	return (1);
}

void	determine_content_of_coordinates(t_common *d_list, char *line, int x, int y)
{
	flush_initial_values(d_list, y);
	while (line[x] && x < d_list->map->raw_length)
	{
		if (line[x] == '1')
			d_list->map->raw_map[x][y] = 1;
		else if (line[x] == '0')
			d_list->map->raw_map[x][y] = 0;
		else if (line[x] == '4')
			d_list->map->raw_map[x][y] = 4;
		else if (line[x] == '3')
		{
			d_list->rc->sprite[0] = x + 0.5;
			d_list->rc->sprite[1] = y + 0.5;
			d_list->map->raw_map[x][y] = 0;
		}
		else if (line[x] == 'N' || line[x] == 'S' || line[x] == 'W' || line[x] == 'E')
		{
			d_list->rc->pos[0] = x + 0.5;
			d_list->rc->pos[1] = y + 0.5;
			d_list->rc->look = line[x] == 'N' ? 0.5 : line[x] == 'S' ? 1 : line[x] == 'W' ? 1.5 : 0;
			d_list->map->raw_map[x][y] = 0;
		}
		x++;
	}
	free(line);
}

void	flush_initial_values(t_common *d_list, int y)
{
	int x;

	x = 0;
	while (x < d_list->map->raw_length)
	{
		d_list->map->raw_map[x][y] = RESIDUUM;
		x++;
	}
}