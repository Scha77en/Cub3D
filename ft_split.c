/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 23:55:42 by aouhbi            #+#    #+#             */
/*   Updated: 2024/01/22 08:12:34 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

static int	rows_num(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*get_word(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	*free_mem(char **ptr, int j)
{
	while (j >= 0)
	{
		free(ptr[j]);
		j--;
	}
	free(ptr);
	return (0);
}

char	**ft_split(char *s, char c)
{
	size_t	g_end;
	size_t	j;
	int		g_start;
	char	**ptr;

	ptr = malloc((rows_num(s, c) + 1) * sizeof(char *));
	if (!s || !ptr)
		return (0);
	g_end = -1;
	j = 0;
	g_start = -1;
	while (++g_end <= ft_strlen(s))
	{
		if (s[g_end] != c && g_start < 0)
			g_start = g_end;
		else if ((s[g_end] == c || g_end == ft_strlen(s)) && g_start >= 0)
		{
			ptr[j++] = get_word(s, g_start, g_end);
			if (!ptr[j - 1])
				return (free_mem(ptr, (j - 1)), NULL);
			g_start = -1;
		}
	}
	return (ptr[j] = 0, ptr);
}

int	ft_atoi(char *str)
{
	int	i;
	int	ishara;
	int	res;

	i = 0;
	ishara = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			ishara *= -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (ishara * res);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	number_check(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		if (!ft_isdigit(str[i]))
		{
			return (error_out("invalid number\n", 0), 0);
		}
		i++;
	}
	if (ft_atoi(str) > 255 || ft_atoi(str) < 0)
		return (error_out("Number out of range\n", 0), 0);
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

void	*ft_calloc(size_t count, size_t size)
{
	int					*ptr;
	unsigned long long	m;

	m = (size * count);
	ptr = (int *)malloc(m);
	if (ptr)
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
