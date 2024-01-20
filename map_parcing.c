/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parcing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 06:22:58 by aouhbi            #+#    #+#             */
/*   Updated: 2024/01/20 18:44:50 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

void	map_parcing(int fd, int size, char *line, t_data **data)
{
	int		i;

	(void)size;
	i = 1;
	(*data)->map = malloc(sizeof(char *) * 6);
	parce_and_save_map_line(line, data, 0);
	free(line);
	while (1)
	{
		printf("after ---------- map[0] = %s\n", (*data)->map[0]);
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\0')
			break ;
		if (line[0] == '\n')
		{
			free(line);
			break ;
		}
		parce_and_save_map_line(line, data, i);
		free(line);
		i++;
	}
	(*data)->map[i] = NULL;
	// print_map(data);
}

void	parce_and_save_map_line(char *line, t_data **data, int v)
{
	int		i;

	i = 0;
	// printf("line = %s\n", line);
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	(*data)->map[v] = ft_strdup(line + i);
}
int		two_d_size(char *f_name)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(f_name, O_RDONLY);
	while (i <= 6)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		free(line);
		i++;
	}
	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\0')
			break ;
		if (line[0] == '\n')
		{
			free(line);
			break ;
		}
		free(line);
		i++;
	}
	close(fd);
	return (i);
}