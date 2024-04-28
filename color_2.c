/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 19:11:06 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:33:22 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"
#include "libft/libft.h"

int	color_plmul_color(t_color *p, t_color *to_sum, float to_mul)
{
	p->red += to_sum->red * to_mul;
	p->green += to_sum->green * to_mul;
	p->blue += to_sum->blue * to_mul;
	return (1);
}

unsigned int	color_mul(unsigned int col, float alpha)
{
	unsigned int	blue;
	unsigned int	green;
	unsigned int	red;

	blue = col & BLUE;
	green = (col & GREEN) >> 8u;
	red = (col & RED) >> 16u;
	blue = (unsigned)((float)blue * alpha);
	green = (unsigned)((float)green * alpha);
	red = (unsigned)((float)red * alpha);
	return (blue | (green << 8u) | (red << 16u));
}

unsigned int	color_mul_rgb(unsigned int col, t_color *alpha)
{
	unsigned int	blue;
	unsigned int	green;
	unsigned int	red;

	blue = col & BLUE;
	green = (col & GREEN) >> 8u;
	red = (col & RED) >> 16u;
	blue = (unsigned)floorf(((float)blue * alpha->blue) + 0.5f);
	green = (unsigned)floorf(((float)green * alpha->green) + 0.5f);
	red = (unsigned)floorf(((float)red * alpha->red) + 0.5f);
	return (blue | (green << 8u) | (red << 16u));
}

unsigned int	color_sum(unsigned int col1, unsigned int col2)
{
	unsigned int	blue;
	unsigned int	green;
	unsigned int	red;

	blue = (col1 & BLUE) + (col2 & BLUE);
	green = ((col1 & GREEN) >> 8u) + ((col2 & GREEN) >> 8u);
	red = ((col1 & RED) >> 16u) + ((col2 & RED) >> 16u);
	blue = ft_min((int)blue, 255);
	green = ft_min((int)green, 255);
	red = ft_min((int)red, 255);
	return (blue | (green << 8u) | (red << 16u));
}
