/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:21:36 by mzolfagh          #+#    #+#             */
/*   Updated: 2024/07/17 16:38:49 by mzolfagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubid.h"

double	dot_product(double p1[2], double p2[2])
{
	return (p1[0] * p2[0] + p1[1] * p2[1]);
}

double	cross_product(double p1[2], double p2[2])
{
	return (p1[0] * p2[1] - p1[1] * p2[0]);
}

double	magnitudes(double p[2])
{
	return (sqrt(pow(p[0], 2) + pow(p[1], 2)));
}
