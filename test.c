/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:54:24 by aouhbi            #+#    #+#             */
/*   Updated: 2024/01/20 16:48:26 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

static void	print_map2(t_data *data)
{
	int		i;

	i = 0;
	while (data->map[i])
	{
		printf("map[%d] == %s\n", i, data->map[i]);
		i++;
	}
}
static void	test_parce(int fd, char *line, t_data **data)
{
	int		i;

	i = 2;
	while (1)
	{
		// printf("after ---------- map[0] = %s\n", (*data)->map[0]);
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\0')
			break ;
		if (line[0] == '\n')
		{
			free(line);
			break ;
		}
		(*data)->map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	(*data)->map[i] = NULL;
}
int main(void)
{
	char *line;
	int fd;
	int i;
	t_data *data;

	i = 0;
	data = malloc(sizeof(t_data));
	data->map = malloc(sizeof(char *) * 100);
	fd = open("map.cub", O_RDONLY);
	while (i <= 1)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\0')
			break ;
		if (line[0] == '\n')
		{
			free(line);
			break ;
		}
		printf("line = %s\n", line);
		data->map[i] = malloc(ft_strlen(line) + 1);
		ft_strlcpy(data->map[i], line, ft_strlen(line) + 1);
		data->map[i][ft_strlen(line)] = '\0';
		free(line);
		i++;
	}
	test_parce(fd, line, &data);
	print_map2(data);
	printf("i = %d\n", i);
	return (0);
}