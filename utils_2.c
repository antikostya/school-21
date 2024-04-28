/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:05:04 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:35:41 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"
#include "libft/libft.h"

int	ft_check_rangef(float f, int mi, int ma, char *message)
{
	if (!(f < (float)mi || f > (float)ma))
		return (0);
	ft_putstr_fd(ERROR "ERROR\n" RESET, 1);
	ft_putstr_fd("Incorrect ", 1);
	ft_putstr_fd(message, 1);
	ft_putstr_fd(" value, it must be in range [", 1);
	ft_putnbr_fd(mi, 1);
	ft_putstr_fd(", ", 1);
	ft_putnbr_fd(ma, 1);
	ft_putstr_fd("]\n", 1);
	return (ft_exit_all(""));
}

int	ft_check_rangei(int i, int mi, int ma, char *message)
{
	if (!(i < mi || i > ma))
		return (0);
	ft_putstr_fd(ERROR "ERROR\n" RESET, 1);
	ft_putstr_fd("Incorrect ", 1);
	ft_putstr_fd(message, 1);
	ft_putstr_fd(" value (", 1);
	ft_putnbr_fd(i, 1);
	ft_putstr_fd("), it must be in range [", 1);
	ft_putnbr_fd(mi, 1);
	ft_putstr_fd(", ", 1);
	ft_putnbr_fd(ma, 1);
	ft_putstr_fd("]\n", 1);
	return (ft_exit_all(""));
}

void	ft_line_free(char **line)
{
	char	**ptr;

	ptr = line;
	if (!line)
		return ;
	while (*line)
		free(*line++);
	free(ptr);
}

int	ft_append_array(void ***array_ptr, size_t wc, size_t size)
{
	void	*new_array;

	new_array = malloc(size * (wc + 1));
	if (!new_array)
		return (1);
	ft_memcpy(new_array, *array_ptr, size * wc);
	ft_bzero((char *)new_array + wc * size, size);
	free(*array_ptr);
	*array_ptr = new_array;
	return (0);
}

int	ft_iscomma(int __c)
{
	return (__c == ',');
}
