/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 21:00:10 by tlucanti          #+#    #+#             */
/*   Updated: 2020/08/23 21:00:16 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	print_state(int *map)
{
	int		i;
	char	c;

	i = -1;
	while (++i < 4)
	{
		c = map[i] / 1000 + 48;
		write(1, &c, 1);
		write(1, " ", 1);
		c = (map[i] / 100) % 10 + 48;
		write(1, &c, 1);
		write(1, " ", 1);
		c = (map[i] / 10) % 10 + 48;
		write(1, &c, 1);
		write(1, " ", 1);
		c = (map[i] % 10) + 48;
		write(1, &c, 1);
		write(1, "\n", 1);
	}
}

void	print_str(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int		*init_vars1(int *a)
{
	a[0] = 0;
	a[1] = 1234;
	a[2] = 1243;
	a[3] = 1324;
	a[4] = 1342;
	a[5] = 1423;
	a[6] = 1432;
	a[7] = 2134;
	a[8] = 2143;
	a[9] = 2314;
	a[10] = 2341;
	a[11] = 2413;
	a[12] = 2431;
	return (a);
}

int		*init_vars2(int *a)
{
	a[13] = 3124;
	a[14] = 3142;
	a[15] = 3214;
	a[16] = 3241;
	a[17] = 3412;
	a[18] = 3421;
	a[19] = 4123;
	a[20] = 4132;
	a[21] = 4213;
	a[22] = 4231;
	a[23] = 4312;
	a[24] = 4321;
	return (a);
}
