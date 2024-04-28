/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:10:06 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:33:44 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"
#include "libft/libft.h"

t_scene *g_scene;

int	main(int argc, char **argv)
{
	int	fd;

	if (argc == 1)
		return (ft_exit_all("No input file"));
	if (init_scene() || check_extention(argv[1]))
		return (0);
	g_scene->dist = 1.f + EPS;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("cannot open ", 1);
		ft_putstr_fd(argv[1], 1);
		ft_putstr_fd(" file\n", 1);
		return (0);
	}
	gui_bootstrap();
	g_scene->window = gui_alloc();
	if (g_scene->window == NULL)
		return (ft_exit_all("malloc error"));
	if (parce_scene(fd))
	{
		close(fd);
		return (0);
	}
	return (main_1(argc, argv));
}

int	do_screenshot(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (argc == 3 && !ft_strcmp(argv[2], "--save"))
	{
		if (gui_create(g_scene->window, g_scene->res_x, g_scene->res_y))
			return (ft_exit_all("malloc error"));
		key_hook(g_scene->window, KEY_P, true);
		gui_destroy(g_scene->window);
		gui_finalize();
		return (1);
	}
	return (0);
}

int	main_1(int argc, char **argv)
{
	if (g_scene->res_x < 0 || g_scene->res_y < 0)
		return (0 * ft_exit_all("resolution not set"));
	if (g_scene->cameras_num == 0)
		return (0 * ft_exit_all("no cameras in scene"));
	if (do_screenshot(argc, argv))
		return (0);
	if (gui_create(g_scene->window, g_scene->res_x, g_scene->res_y))
		return (ft_exit_all("malloc error"));
	gui_key_hook(g_scene->window, key_hook);

	while (true) {
		gui_wfi(g_scene->window);
	}
	return (0);
}

int	check_extention(char *fname)
{
	int	size;

	size = ft_strlen(fname);
	if (size < 3 || fname[size - 3] != '.' || fname[size - 2] != 'r'
		|| fname[size - 1] != 't')
	{
		ft_putstr_fd(ERROR "Error" RESET, 1);
		ft_putstr_fd("\nwrong file name/extention\n", 1);
		return (1);
	}
	return (0);
}
