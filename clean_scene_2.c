/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_scene_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:41:54 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:33:16 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"

void	free_cylinders(t_cylinder **cy, int num)
{
	while (num)
	{
		free(cy[num - 1]->center);
		free(cy[num - 1]->q);
		free(cy[num - 1]);
		num--;
	}
	free(cy);
}

void	free_circles(t_circle **cr, int num)
{
	while (num)
	{
		free(cr[num - 1]->center);
		free(cr[num - 1]->normal);
		free(cr[num - 1]);
		num--;
	}
	free(cr);
}

void	free_lights(t_light **li, int num)
{
	while (num)
	{
		free(li[num - 1]->color);
		free(li[num - 1]->vect);
		free(li[num - 1]);
		num--;
	}
	free(li);
}

void	free_cameras(t_camera **cam, int num)
{
	while (num)
	{
		free(cam[num - 1]->o);
		free(cam[num - 1]->view_vector);
		free(cam[num - 1]->rotation_matrix);
		free(cam[num - 1]);
		num--;
	}
	free(cam);
}

int	ft_close_window(int code, void	*_)
{
	(void)code;
	(void)_;
	gui_destroy(g_scene->window);
	ft_clean_scene();
	gui_finalize();
	g_scene = NULL;
	exit(0);
}
