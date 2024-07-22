/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:28:31 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 16:52:54 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

int	error_arguments(int argc, char **argv)
{
	int	fd;
	int	i;

	fd = 0;
	i = 0;
	if (argc != 2 || !argv[1])
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (0);
	i = ft_strlen(argv[1]);
	i--;
	if (argv[1][i] != 'b' || argv[1][i - 1] != 'u'
		|| argv[1][i - 2] != 'c' || argv[1][i - 3] != '.')
	{
		ft_printf("Error\nInvalid file extension\n");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

void	p_error(char *str, t_common *d_list)
{
	ft_printf("%s\n", str);
	cleanup(d_list);
	exit(0);
}
