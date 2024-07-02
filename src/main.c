/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:29:31 by fmarggra          #+#    #+#             */
/*   Updated: 2024/06/26 20:29:33 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int main(int argc, char **argv)
{
    t_common  d_list;
    
    //this should be taken out later
    if (check_the_textures_open() == 0)
      return (0);
    if (error_arguments(argc, argv) == 0)
        return (0);
    if (init_structs(&d_list, argv[1]) == 0)
      return (0);
    if (!read_map_from_file(&d_list))
      return (0);
    if (init_mlx_functions(&d_list) == 0)
      return 0;
   // test_map(&d_list);
    if (minimap(&d_list) == 0)
      return (cleanup(&d_list), 0);
    put_image(&d_list, d_list.mlx);
    events(&d_list);
    // //basic 3d array for testing --> d_list->map->raw_map
    // //read from the map_file
    cleanup(&d_list);
    return 1;
}
