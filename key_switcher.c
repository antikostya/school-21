/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_switcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:57:28 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:33:34 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"

#define MOVE_STEP 0.5f
#define LOOK_ANGLE 0.157079632675f

int	key_switcher_1(int keycode, t_point *n)
{
	if (keycode == KEY_UP)
	{
		g_scene->current_camera->alpha -= LOOK_ANGLE
			* sinf(g_scene->current_camera->gamma);
		g_scene->current_camera->theta -= LOOK_ANGLE
			* cosf(g_scene->current_camera->gamma);
		return (0);
	}
	else if (keycode == KEY_DOWN)
	{
		g_scene->current_camera->alpha += LOOK_ANGLE
			* sinf(g_scene->current_camera->gamma);
		g_scene->current_camera->theta += LOOK_ANGLE
			* cosf(g_scene->current_camera->gamma);
		return (0);
	}
	else if (keycode == KEY_W)
	{
		*n = point_stack(0, 0, MOVE_STEP);
		matrix3_mul(g_scene->current_camera->rotation_matrix, n);
		point_plus_point(g_scene->current_camera->o, n);
		return (0);
	}
	else
		return (key_switcher_2(keycode, n));
}

int	key_switcher_2(int keycode, t_point *n)
{
	if (keycode == KEY_RIGHT)
	{
		g_scene->current_camera->alpha += LOOK_ANGLE
			* cosf(g_scene->current_camera->gamma);
		g_scene->current_camera->theta -= LOOK_ANGLE
			* sinf(g_scene->current_camera->gamma);
		return (0);
	}
	else if (keycode == KEY_LEFT)
	{
		g_scene->current_camera->alpha -= LOOK_ANGLE
			* cosf(g_scene->current_camera->gamma);
		g_scene->current_camera->theta += LOOK_ANGLE
			* sinf(g_scene->current_camera->gamma);
		return (0);
	}
	else if (keycode == KEY_S)
	{
		*n = point_stack(0, 0, -MOVE_STEP);
		matrix3_mul(g_scene->current_camera->rotation_matrix, n);
		point_plus_point(g_scene->current_camera->o, n);
		return (0);
	}
	else
		return (key_switcher_3(keycode, n));
}

int	key_switcher_3(int keycode, t_point *n)
{
	if (keycode == KEY_A)
	{
		*n = point_stack(-MOVE_STEP, 0, 0);
		matrix3_mul(g_scene->current_camera->rotation_matrix, n);
		point_plus_point(g_scene->current_camera->o, n);
		return (0);
	}
	else if (keycode == KEY_D)
	{
		*n = point_stack(MOVE_STEP, 0, 0);
		matrix3_mul(g_scene->current_camera->rotation_matrix, n);
		point_plus_point(g_scene->current_camera->o, n);
		return (0);
	}
	else if (keycode == KEY_SPACE)
	{
		*n = point_stack(0, MOVE_STEP, 0);
		matrix3_mul(g_scene->current_camera->rotation_matrix, n);
		point_plus_point(g_scene->current_camera->o, n);
		return (0);
	}
	else
	{
		return (key_switcher_4(keycode, n));
	}
}

int	key_switcher_4(int keycode, t_point *n)
{
	if (keycode == KEY_LCTRL || keycode == KEY_RCTRL)
	{
		*n = point_stack(0, -MOVE_STEP, 0);
		matrix3_mul(g_scene->current_camera->rotation_matrix, n);
		point_plus_point(g_scene->current_camera->o, n);
		return (0);
	}
	else if (keycode == KEY_Q)
	{
		g_scene->current_camera->gamma += LOOK_ANGLE;
		return (0);
	}
	else if (keycode == KEY_E)
	{
		g_scene->current_camera->gamma -= LOOK_ANGLE;
		return (0);
	}
	if (keycode == KEY_X)
	{
		ft_close_window(0, NULL);
		return (1);
	}
	else
		return (key_switcher_5(keycode));
}

int	key_switcher_5(int keycode)
{
	if (keycode == KEY_ENTER && g_scene->cameras_num > 1)
	{
		g_scene->current_camera_num++;
		g_scene->current_camera_num %= g_scene->cameras_num;
		g_scene->current_camera = g_scene->cameras[g_scene->current_camera_num];
		return (0);
	}
	else if (keycode != KEY_P && keycode != 0)
		return (1);
	return (0);
}
