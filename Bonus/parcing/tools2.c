/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:23:49 by aouhbi            #+#    #+#             */
/*   Updated: 2024/02/04 18:19:46 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	number_check(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (error_out("invalid number\n", 0, data), 0);
		i++;
	}
	if (ft_strlen(str) > 3 || ft_atoi(str) > 255 || ft_atoi(str) < 0)
		return (error_out("Number out of range\n", 0, data), 0);
	return (1);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	size_t	slen;

	slen = ft_strlen(s1) + 1;
	ptr = (char *)malloc(slen);
	if (!ptr || !s1)
		return (0);
	ft_memcpy(ptr, s1, (size_t)slen);
	return (ptr);
}

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t	i;
	char	*s;
	char	*d;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	if (src == 0 && dst == 0)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
