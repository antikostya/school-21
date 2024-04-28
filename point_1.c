/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:51:42 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:34:32 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"

t_point	*point(float x, float y, float z)
{
	t_point	*new_point;

	new_point = (t_point *)malloc(sizeof(t_point));
	new_point->x = x;
	new_point->y = y;
	new_point->z = z;
	return (new_point);
}

t_point	*point_minus(t_point *p1, t_point *p2)
{
	t_point	*new_point;

	new_point = (t_point *)malloc(sizeof(t_point));
	new_point->x = p1->x - p2->x;
	new_point->y = p1->y - p2->y;
	new_point->z = p1->z - p2->z;
	return (new_point);
}

t_point	*point_plus(t_point *p1, t_point *p2)
{
	t_point	*new_point;

	new_point = (t_point *)malloc(sizeof(t_point));
	new_point->x = p1->x + p2->x;
	new_point->y = p1->y + p2->y;
	new_point->z = p1->z + p2->z;
	return (new_point);
}

t_point	*point_cross(t_point *p1, t_point *p2)
{
	t_point		*new_point;

	new_point = (t_point *)malloc(sizeof(t_point));
	if (!new_point)
		return (NULL);
	new_point->x = det2(p1->y, p1->z, p2->y, p2->z);
	new_point->y = -(det2(p1->x, p1->z, p2->x, p2->z));
	new_point->z = det2(p1->x, p1->y, p2->x, p2->y);
	return (new_point);
}
