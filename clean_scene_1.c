/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_scene_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:41:33 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:33:14 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"

void	ft_clean_scene(void)
{
	if (!g_scene)
		return ;
	free_spheres(g_scene->spheres, g_scene->spheres_num);
	free_planes(g_scene->planes, g_scene->planes_num);
	free_triangles(g_scene->triangles, g_scene->triangles_num);
	free_squares(g_scene->squares, g_scene->squares_num);
	free_cylinders(g_scene->cylinders, g_scene->cylinders_num);
	free_circles(g_scene->circles, g_scene->circles_num);
	free_lights(g_scene->lights, g_scene->lights_num);
	free_cameras(g_scene->cameras, g_scene->cameras_num);
	free(g_scene);
	g_scene = NULL;
}

void	free_spheres(t_sphere **sp, int num)
{
	while (num)
	{
		free(sp[num - 1]->center);
		free(sp[num - 1]);
		num--;
	}
	free(sp);
}

void	free_planes(t_plane **pl, int num)
{
	while (num)
	{
		free(pl[num - 1]->point);
		free(pl[num - 1]->normal);
		free(pl[num - 1]);
		num--;
	}
	free(pl);
}

void	free_triangles(t_triangle **tr, int num)
{
	while (num)
	{
		free(tr[num - 1]->normal);
		free(tr[num - 1]->a);
		free(tr[num - 1]->b);
		free(tr[num - 1]->c);
		free(tr[num - 1]->ab);
		free(tr[num - 1]->bc);
		free(tr[num - 1]->ca);
		free(tr[num - 1]);
		num--;
	}
	free(tr);
}

void	free_squares(t_square **sq, int num)
{
	while (num)
	{
		free(sq[num - 1]->center);
		free(sq[num - 1]->normal);
		free(sq[num - 1]->v1);
		free(sq[num - 1]->v2);
		free(sq[num - 1]);
		num--;
	}
	free(sq);
}
