/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parcer_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:44:35 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/22 12:26:43 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

int	init_scene(void)
{
	g_scene = (t_scene *)malloc(sizeof(t_scene));
	if (g_scene == NULL)
		return (ft_exit_all("Malloc error"));
	g_scene->res_x = -1;
	g_scene->res_y = -1;
	g_scene->cameras_num = 0;
	g_scene->spheres_num = 0;
	g_scene->planes_num = 0;
	g_scene->triangles_num = 0;
	g_scene->squares_num = 0;
	g_scene->circles_num = 0;
	g_scene->cylinders_num = 0;
	g_scene->lights_num = 0;
	g_scene->cameras = NULL;
	g_scene->spheres = NULL;
	g_scene->planes = NULL;
	g_scene->triangles = NULL;
	g_scene->squares = NULL;
	g_scene->circles = NULL;
	g_scene->cylinders = NULL;
	g_scene->lights = NULL;
	return (0);
}

int	parce_scene(int fd)
{
	char	*line;
	int		ret;
	char	**splt;
	int		gnl;

	gnl = get_next_line(fd, &line);
	while (gnl != -1)
	{
		splt = ft_split(line, ft_isspace);
		if (!splt)
			return (ft_exit_all("Malloc error"));
		ret = switcher(splt);
		ft_line_free(splt);
		free(line);
		if (ret)
			return (1);
		if (gnl == 0)
			return (0);
		gnl = get_next_line(fd, &line);
	}
	return (ft_exit_all("File read or malloc error"));
}

int	switcher(char **splt)
{
	if (!*splt || **splt == '#')
		return (0);
	else if (!ft_strcmp(*splt, "R") || !ft_strcmp(*splt, "r"))
		return (ft_set_resolution(splt));
	else if (!ft_strcmp(*splt, "A") || !ft_strcmp(*splt, "a"))
		return (ft_add_ambient(splt));
	else if (!ft_strcmp(*splt, "c"))
		return (ft_add_camera(splt));
	else if (!ft_strcmp(*splt, "l"))
		return (ft_add_point(splt));
	else if (!ft_strcmp(*splt, "sp"))
		return (ft_add_sphere(splt));
	else if (!ft_strcmp(*splt, "pl"))
		return (ft_add_plane(splt));
	else if (!ft_strcmp(*splt, "sq"))
		return (ft_add_square(splt));
	else if (!ft_strcmp(*splt, "cy"))
		return (ft_add_cylinder(splt));
	else if (!ft_strcmp(*splt, "tr"))
		return (ft_add_triangle(splt));
	else if (!ft_strcmp(*splt, "d"))
		return (ft_add_direct(splt));
	return (0);
}

int	ft_set_resolution(char **line)
{
	if (ft_array_size(line) < 3)
		return (ft_exit_all("Incorrect resolution configuration"));
	g_scene->res_x = ft_atoi(line[1]);
	g_scene->res_y = ft_atoi(line[2]);
	if (ft_check_rangei(g_scene->res_x, 1, 0x7fffffff, "resolution")
		|| ft_check_rangei(g_scene->res_y, 1, 0x7fffffff, "resolution"))
		return (1);
	return (0);
}

int	ft_add_ambient(char **line)
{
	t_light_input	inp;
	size_t			size;

	size = ft_array_size(line);
	if (size < 2)
		return (ft_exit_all("Incorrect ambient light configuration"));
	inp.type = 'a';
	inp.intensity = ft_atof(line[1]);
	if (size < 3)
		inp.rgb = color(1, 1, 1, inp.intensity);
	else
		inp.rgb = color_str_struct(line[2], inp.intensity);
	inp.vect = NULL;
	if (!inp.rgb || ft_check_rangef(inp.intensity, 0, 1,
			"ambient light intensity"))
		return (1);
	if (ft_append_array((void ***) &g_scene->lights, g_scene->lights_num,
			sizeof(t_light *)))
		return (ft_exit_all("Malloc error") + ft_free(inp.rgb));
	if (light(&inp, g_scene->lights + g_scene->lights_num++))
		return (ft_exit_all("Malloc error"));
	return (0);
}
