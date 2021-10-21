/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 11:26:09 by tlucanti          #+#    #+#             */
/*   Updated: 2020/08/15 11:26:13 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, char *src)
{
	char *ans;

	ans = dest;
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (ans);
}
