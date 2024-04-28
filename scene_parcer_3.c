/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parcer_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:03:08 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/22 12:42:47 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"
#include "libft/libft.h"

int	ft_add_square(char **line)
{
	t_square_input	inp;
	int				size;

	size = ft_array_size(line);
	if (size < 5)
		return (ft_exit_all("Incorrect square configuration"));
	inp.center = point_str(line[1]);
	inp.normal = point_str(line[2]);
	inp.d = ft_atof(line[3]);
	inp.col = color_str(line[4]);
	inp.specular = tern_atoi(size >= 6, 200, line[5]);
	inp.reflective = tern_atof(size >= 7, -1.f, line[6]);
	if (!inp.center || !inp.normal || inp.col == 0xffffffff
		|| ft_check_rangef(inp.d, 0, 0x7fffffff, "square side size")
		|| ft_check_rangef(inp.reflective, 0xffffffff, 1, "square reflective"))
		return (1 + ft_free(inp.center) + ft_free(inp.normal));
	if (ft_append_array((void ***) &g_scene->squares, g_scene->squares_num,
			sizeof(t_square *)))
		return (ft_exit_all("Malloc error")
			+ ft_free(inp.center) + ft_free(inp.normal));
	if (square(&inp, g_scene->squares + g_scene->squares_num++))
		return (ft_exit_all("Malloc error"));
	ft_normalize_vect(inp.normal, "square normal");
	return (0);
}

int	ft_add_cylinder(char **line)
{
	t_cylinder_input	inp;
	int					size;

	size = ft_array_size(line);
	if (size < 6)
		return (ft_exit_all("Incorrect cylinder configuration"));
	inp.center = point_str(line[1]);
	inp.vec = point_str(line[2]);
	inp.col = color_str(line[3]);
	masf2(&inp.d, ft_atof(line[4]), &inp.h, ft_atof(line[5]));
	inp.specular = tern_atoi(size >= 7, 200, line[6]);
	inp.reflective = tern_atof(size >= 8, -1.f, line[7]);
	if (!inp.center || !inp.vec || inp.col == 0xffffffff
		|| ft_check_rangef(inp.d, 0, 0x7fffffff, "cylinder diameter")
		|| ft_check_rangef(inp.reflective, -1, 1, "cylinder reflective")
		|| ft_check_rangef(inp.h, 0, 0x7fffffff, "cylinder height"))
		return (1 + ft_free(inp.center) + ft_free(inp.vec));
	if (ft_append_array((void ***) &g_scene->cylinders, g_scene->cylinders_num,
			sizeof(t_cylinder *)))
		return (ft_exit_all("Malloc error") + ft_free(inp.center)
			+ ft_free(inp.vec));
	if (cylinder(&inp, g_scene->cylinders + g_scene->cylinders_num++))
		return (ft_exit_all("Malloc error"));
	ft_normalize_vect(inp.vec, "cylinder direction");
	return (0);
}

int	ft_add_triangle(char **line)
{
	t_triangle_input	inp;
	int					size;

	size = ft_array_size(line);
	if (size < 5)
		return (ft_exit_all("Incorrect triangle configuration"));
	inp.x = point_str(line[1]);
	inp.y = point_str(line[2]);
	inp.z = point_str(line[3]);
	inp.col = color_str(line[4]);
	inp.specular = tern_atoi(size >= 6, 200, line[5]);
	inp.reflective = tern_atof(size >= 7, -1.f, line[6]);
	if (!inp.x || !inp.y || !inp.z || inp.col == 0xffffffff
		|| ft_check_rangef(inp.reflective, -1, 1, "triangle reflective"))
		return (1 + ft_free(inp.x) + ft_free(inp.y) + ft_free(inp.z));
	if (ft_append_array((void ***) &g_scene->triangles, g_scene->triangles_num,
			sizeof(t_triangle *)))
		return (ft_exit_all("Malloc error")
			+ ft_free(inp.x) + ft_free(inp.y) + ft_free(inp.z));
	if (triangle(&inp, g_scene->triangles + g_scene->triangles_num++))
		return (ft_exit_all("Malloc error"));
	return (0);
}
