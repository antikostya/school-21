/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:33:38 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:33:38 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"

void	key_hook(struct gui_window *window, int keycode, bool pressed)
{
	t_point	n;

	if (!pressed)
		return ;
	if (key_switcher_1(keycode, &n))
		return ;
	rotate_matrix(g_scene->current_camera->rotation_matrix, g_scene
		->current_camera->alpha, g_scene->current_camera
		->theta, g_scene->current_camera->gamma);
	minirt_loop();
	if (keycode == KEY_P)
		screenshot("./scr.bmp");
	gui_draw(window);
	return ;
}

void	minirt_loop(void)
{
	t_pair	t_min_max;
	t_point	d;
	int		x;
	int		y;

	t_min_max.t_min = 1;
	t_min_max.t_max = INF;
	x = -g_scene->res_x / 2;
	while (x < g_scene->res_x / 2)
	{
		y = -g_scene->res_y / 2;
		while (y < g_scene->res_y / 2)
		{
			d = (t_point){(float) x * g_scene->current_camera->fovx, (float) y
				* g_scene->current_camera->fovy, g_scene->dist};
			matrix3_mul(g_scene->current_camera->rotation_matrix, &d);
			unsigned color = trace_ray(g_scene->current_camera->o, &d,
					&t_min_max, 1);
			gui_set_pixel(g_scene->window,
				      g_scene->res_x / 2 + x,
				      g_scene->res_y / 2 - y - 1,
				      color);
			y++;
		}
		x++;
	}
}
