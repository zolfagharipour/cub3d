/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:28:42 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 18:48:28 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

void	init_validity_params(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 6)
		map->val_aspects[i] = NOT_FOUND;
	i = -1;
	while (++i < 6)
		map->val_map[i] = 0;
	i = -1;
	while (++i < 19)
		map->textures[i] = NULL;
}
