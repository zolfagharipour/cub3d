#include "cubid.h"

int	is_texture(int i, char *line, char id, char id2)
{
	if (line[i] && line[i + 1] && line [i + 2] && line[i] == id
		&& line[i + 1] == id2 && line[i + 2] == ' ')
		return (1);
	return (0);
}

int all_ids_found(t_common *d_list)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (d_list->map->val_aspects[i] == NOT_FOUND)
			return (0);
		i++;
	}
	return (1);
}
