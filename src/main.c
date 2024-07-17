/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:31 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:32:27 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	main(int argc, char **argv)
{
	t_common	d_list;

	if (error_arguments(argc, argv) == 0)
		return (0);
	if (init_structs(&d_list, argv[1]) == 0)
		return (0);
	if (!read_map_from_file(&d_list))
		return (0);
	if (init_mlx_functions(&d_list, &d_list.mlx[0]) == 0)
		return (0);
	if (minimap(&d_list) == 0)
		return (cleanup(&d_list), 0);
	put_image(&d_list, &d_list.mlx[0]);
	events(&d_list);
	cleanup(&d_list);
	return (1);
}
