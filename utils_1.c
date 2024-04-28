/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:35:34 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:35:37 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_traycer.h"
#include "libft/libft.h"

t_point	*reflect_ray(t_point *l, t_point *n)
{
	float	dt;

	dt = 2.f * dot(n, l);
	l->x = n->x * dt - l->x;
	l->y = n->y * dt - l->y;
	l->z = n->z * dt - l->z;
	return (l);
}

void	*ft_realloc(void *ptr, size_t size, size_t new_size)
{
	char	*new_ptr;
	char	*my_ptr;
	size_t	i;

	new_ptr = (char *) malloc (new_size);
	my_ptr = (char *)ptr;
	i = 0;
	while (i < size)
	{
		new_ptr[i] = my_ptr[i];
		i++;
	}
	return (new_ptr);
}

int	ft_array_size(char **arr)
{
	int		size;

	if (arr == NULL)
		return (-1);
	size = 0;
	while (*arr++)
		size++;
	return (size);
}

void	ft_normalize_vect(t_point *p, char *message)
{
	float		length;

	length = p->x * p->x + p->y * p->y + p->z * p->z;
	if (fabsf(length - 1) > 1e-3)
	{
		ft_putstr_fd(WARNING"Warning"RESET, 1);
		ft_putstr_fd(", ", 1);
		ft_putstr_fd(message, 1);
		ft_putstr_fd(" vector is not normalized, scaling its length to 1\n", 1);
		normalize(p);
	}
}
