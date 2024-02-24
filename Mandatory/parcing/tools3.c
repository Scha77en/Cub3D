/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:24:55 by aouhbi            #+#    #+#             */
/*   Updated: 2024/02/04 17:57:43 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	*ft_calloc(size_t count, size_t size)
{
	int					*ptr;
	unsigned long long	m;

	m = (size * count);
	ptr = (int *)malloc(m);
	if (!ptr)
		error_out("malloc", 1, NULL);
	else if (ptr)
		ft_bzero((char *)ptr, m);
	return (ptr);
}

void	*ft_memset(void *b, int c, size_t len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		len--;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

int	check_spaces(char c, int *k, int *j)
{
	if (c == ' ')
	{
		(*k)++;
		(*j)++;
		return (1);
	}
	return (0);
}
