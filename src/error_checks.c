/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:28:31 by fmarggra          #+#    #+#             */
/*   Updated: 2024/06/26 20:28:34 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int error_arguments(int argc, char **argv)
{
    int fd;

    fd = 0;
    //opens the file and checks if it exists
    //if it does not exist, return 0
    //if it does exist, close file and return 1
    if (argc != 2 || !argv[1])
        return (0);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (0);
    close(fd);
    return 1;
}

void    p_error(char *str, t_common *d_list)
{
    ft_printf("Error\n%s\n", str);
    cleanup(d_list);
    exit(0);
}
