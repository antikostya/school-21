/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 21:49:43 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:35:23 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"
#include "libft/libft.h"

float	tern_f(int cond, float tru, float flse)
{
	if (cond)
		return (tru);
	return (flse);
}

int	tern_i(int cond, int tru, int flse)
{
	return (cond * tru + !cond * flse);
}

int	tern_atoi(int cond, int flse, char *str)
{
	if (cond)
		return (ft_atoi(str));
	return (flse);
}

float	tern_atof(int cond, float flse, char *str)
{
	if (cond)
		return (ft_atof(str));
	return (flse);
}
