/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parcer_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:35:00 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:35:02 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"
#include "libft/libft.h"

int	ft_exit_all(char *message)
{
	ft_putstr_fd("Error\n", 1);
	if (message[0])
	{
		ft_putstr_fd(message, 1);
		ft_putstr_fd("\n", 1);
	}
	ft_clean_scene();
	return (1);
}

t_color	*color_str_struct(char *line, float intensity)
{
	char		**splt;
	t_color		*col;
	int			rgb[3];

	splt = ft_split(line, ft_iscomma);
	if (!splt)
		return ((t_color *)(size_t)(0 * ft_exit_all("Malloc error")));
	if (ft_array_size(splt) != 3)
	{
		ft_line_free(splt);
		ft_exit_all("Incorrect color configuration");
		return (NULL);
	}
	rgb[0] = ft_atoi(splt[0]);
	rgb[1] = ft_atoi(splt[1]);
	rgb[2] = ft_atoi(splt[2]);
	ft_line_free(splt);
	if (ft_check_rangei(rgb[0], 0, 255, "red color") || ft_check_rangei(rgb[1],
			0, 255, "green color") || ft_check_rangei(rgb[2], 0, 255, "blue col"
			"or") || ft_check_rangef(intensity, 0, 1, "color intensity"))
		return (NULL);
	col = color(rgb[0] / 255.f, rgb[1] / 255.f, rgb[2] / 255.f, intensity);
	if (!col)
		return ((t_color *)(size_t)(0 * ft_exit_all("Malloc error")));
	return (col);
}

t_point	*point_str(char *line)
{
	char	**splt;
	t_point	*p;

	splt = ft_split(line, ft_iscomma);
	if (!splt)
	{
		ft_exit_all("Malloc error");
		return (NULL);
	}
	if (ft_array_size(splt) != 3)
	{
		ft_line_free(splt);
		ft_exit_all("Incorrect vector/point configuration");
		return (NULL);
	}
	p = point(ft_atof(splt[0]), ft_atof(splt[1]), ft_atof(splt[2]));
	ft_line_free(splt);
	if (!p)
	{
		ft_exit_all("Malloc error");
		return (NULL);
	}
	return (p);
}

unsigned int	color_str(char *line)
{
	char			**splt;
	int				rgb[3];

	splt = ft_split(line, ft_iscomma);
	if (!splt)
		return (ft_exit_all("Malloc error") * 0 - 1);
	if (ft_array_size(splt) != 3)
	{
		ft_line_free(splt);
		return (ft_exit_all("Incorrect color configuration") * 0 - 1);
	}
	rgb[0] = ft_atoi(splt[0]);
	rgb[1] = ft_atoi(splt[1]);
	rgb[2] = ft_atoi(splt[2]);
	ft_line_free(splt);
	if (ft_check_rangei(rgb[0], 0, 255, "color") || ft_check_rangei(rgb[1], 0,
			255, "color") || ft_check_rangei(rgb[2], 0, 255, "color"))
		return (-1);
	return (((unsigned)rgb[0] << 16u)
		| ((unsigned)rgb[1] << 8u) | (unsigned)rgb[2]);
}
