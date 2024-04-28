/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parcer_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:53:55 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:34:54 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"
#include "libft/libft.h"

int	ft_add_camera(char **line)
{
	t_camera_input	inp;

	if (ft_array_size(line) < 4)
		return (ft_exit_all("Incorrect camera configuration"));
	inp.o = point_str(line[1]);
	inp.view_vector = point_str(line[2]);
	inp.fovx = ft_atof(line[3]);
	inp.fovy = inp.fovx;
	if (!inp.o || !inp.view_vector
		|| ft_check_rangef(inp.fovx, 0, 180, "fov"))
		return (ft_free(inp.o) + ft_free(inp.view_vector) + 1);
	if (ft_append_array((void ***)&g_scene->cameras, g_scene->cameras_num,
			sizeof(t_camera *)))
		return (ft_exit_all("Malloc error") + ft_free(inp.o)
			+ ft_free(inp.view_vector));
	if (camera(&inp, g_scene->cameras + g_scene->cameras_num++))
		return (ft_exit_all("Maloc error"));
	ft_normalize_vect(inp.view_vector, "camera view");
	g_scene->current_camera = g_scene->cameras[0];
	g_scene->current_camera_num = 0;
	return (0);
}

int	ft_add_point(char **line)
{
	t_light_input	inp;
	size_t			size;

	size = ft_array_size(line);
	if (size < 3)
		return (ft_exit_all("Incorrect point light configuration"));
	inp.type = 'p';
	inp.intensity = ft_atof(line[2]);
	if (size > 3)
		inp.rgb = color_str_struct(line[3], inp.intensity);
	else
		inp.rgb = color(1, 1, 1, inp.intensity);
	inp.vect = point_str(line[1]);
	if (!inp.rgb || !inp.vect || ft_check_rangef(inp.intensity, 0, 1,
			"point light intensity"))
		return (ft_free(inp.rgb) + ft_free(inp.vect) + 1);
	if (ft_append_array((void ***) &g_scene->lights, g_scene->lights_num,
			sizeof(t_light *)))
		return (ft_exit_all("Malloc error") + ft_free(inp.rgb)
			+ ft_free(inp.vect));
	if (light(&inp, g_scene->lights + g_scene->lights_num++))
		return (ft_exit_all("Malloc error"));
	return (0);
}

int	ft_add_direct(char **line)
{
	t_light_input	inp;
	size_t			size;

	size = ft_array_size(line);
	if (size < 3)
		return (ft_exit_all("Incorrect point light configuration"));
	inp.type = 'd';
	inp.intensity = ft_atof(line[2]);
	if (size > 3)
		inp.rgb = color_str_struct(line[3], inp.intensity);
	else
		inp.rgb = color(1, 1, 1, inp.intensity);
	inp.vect = point_str(line[1]);
	if (!inp.rgb || !inp.vect)
		return (ft_free(inp.rgb), ft_free(inp.vect));
	if (ft_append_array((void ***) &g_scene->lights, g_scene->lights_num,
			sizeof(t_light *)))
		return (ft_exit_all("Malloc error") + ft_free(inp.rgb)
			+ ft_free(inp.vect));
	if (light(&inp, g_scene->lights + g_scene->lights_num++))
		return (ft_exit_all("Malloc error"));
	ft_normalize_vect(inp.vect, "direct light");
	return (0);
}

int	ft_add_sphere( char **line)
{
	t_sphere_input	inp;
	int				size;

	size = ft_array_size(line);
	if (size < 4)
		return (ft_exit_all("Incorrect sphere configuration"));
	inp.center = point_str(line[1]);
	inp.radius = ft_atof(line[2]);
	inp.col = color_str(line[3]);
	inp.specular = 200;
	if (size >= 5)
		inp.specular = ft_atoi(line[4]);
	inp.reflective = -1.f;
	if (size >= 6)
		inp.reflective = ft_atof(line[5]);
	if (!inp.center || !inp.radius || inp.col == 0xffffffff
		|| ft_check_rangef(inp.reflective, 0xffffffff, 1, "sphere reflective")
		|| ft_check_rangef(inp.radius, 0, 0x7fffffff, "sphere radius"))
		return (1 + ft_free(inp.center));
	if (ft_append_array((void ***) &g_scene->spheres, g_scene->spheres_num,
			sizeof(t_sphere *)))
		return (ft_exit_all("Malloc error") + ft_free(inp.center));
	if (sphere(&inp, g_scene->spheres + g_scene->spheres_num++))
		return (ft_exit_all("Malloc error"));
	return (0);
}

int	ft_add_plane(char **line)
{
	t_plane_input	inp;
	int				size;

	size = ft_array_size(line);
	if (size < 4)
		return (ft_exit_all("Incorrect plane configuration"));
	inp.p = point_str(line[1]);
	inp.normal = point_str(line[2]);
	inp.col = color_str(line[3]);
	inp.specular = tern_atoi(size >= 5, 200, line[4]);
	inp.reflective = tern_atof(size >= 6, -1.f, line[6]);
	if (!inp.p || !inp.normal || inp.col == 0xffffffff
		|| ft_check_rangef(inp.reflective, 0xffffffff, 1, "plane reflective"))
		return (1 + ft_free(inp.p) + ft_free(inp.normal));
	if (ft_append_array((void ***) &g_scene->planes, g_scene->planes_num,
			sizeof(t_plane *)))
		return (ft_exit_all("Malloc error")
			+ ft_free(inp.p) + ft_free(inp.normal));
	if (plane(&inp, g_scene->planes + g_scene->planes_num++))
		return (ft_exit_all("Malloc error"));
	ft_normalize_vect(inp.normal, "plane normal");
	return (0);
}
