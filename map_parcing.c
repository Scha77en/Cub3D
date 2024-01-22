/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parcing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 06:22:58 by aouhbi            #+#    #+#             */
/*   Updated: 2024/01/22 12:38:52 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

void	map_parcing(int fd, int size, char *line, t_data **data, size_t length)
{
	int		i;

	i = 1;
	(*data)->map = malloc(sizeof(char *) * size);
	parce_and_save_map_line(line, data, 0, length);
		// printf("line = %s\n", line);
	// free(line);
	while (1)
	{
		// free(line);
		// printf("after ---------- map[0] = %s\n", (*data)->map[0]);
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\0')
			break ;
		if (line[0] == '\n')
		{
			free(line);
			break ;
		}
		parce_and_save_map_line(line, data, i, length);
		// free(line);
		i++;
	}
	(*data)->map[i] = NULL;
	// print_map(data);
	check_the_map(data);
}

void	parce_and_save_map_line(char *line, t_data **data, int v, size_t length)
{
	size_t		i;
	size_t		j;
	t_data		*current;

	i = 0;
	j = 0;
	current = *data;
	line = clean_tabs(line);
	current->map[v] = calloc(length + 1, sizeof(char));
	while (line[i] && line[i] != '\n')
		current->map[v][j++] = line[i++];
	while (j < length)
	{
		current->map[v][j] = ' ';
		j++;
	}
	current->map[v][j] = '\0';
	// free(line);
	printf("current->map[%d] = [%s]\nlength = %zu\n", v, current->map[v], length);
}

int		two_d_size(char *f_name, size_t *length)
{
	int		i;
	int		fd;
	char	*line;

	*length = 0;
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
		if (*length < ft_strlen(line))
			*length = ft_strlen(line) - 1;
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
	// printf("i = %d\n", i);
	return (i);
}

void	check_the_map(t_data **data)
{
	int		i;
	int		j;
	int		v;
	int		k;
	t_data	*current;

	i = 0;
	j = 0;
	v = 0;
	k = 0;
	current = *data;
	// print_map(data);
	while (current->map[i][j] && current->map[i][j] != '\n')
	{
		if (current->map[i][j] != '1' && current->map[i][j] != ' ')
		{
			puts("[1]");
			error_out("The walls have a hole :D!\n", 0);
		}
		j++;
	}
	i++;
	print_map(data);
	while (current->map[i + 1])
	{
		j = 0;
		k = 0;
		while (current->map[i][j] && current->map[i][j] != '\n')
		{
			// printf("9able i = %d\n", i);
			if (current->map[i][j] == ' ')
			{
				k++;
				j++;
				continue ;
			}
			// printf("k = %d\n", k);
			// printf("current->map[i][lastvalue] = %c\n", current->map[i][last_value(current->map[i])]);
			// printf("current->map[i][k] = %c\n", current->map[i][k]);                
			if (current->map[i][k] != '1' || current->map[i][last_value(current->map[i])] != '1')
			{
				error_out("The borders are brocken!\n", 0);
			}
			if (current->map[i][j] != '1' && current->map[i][j] != '0' && current->map[i][j] != ' ')
			{
				if (v > 0)
					error_out("There is more than one player on the map!\n", 0);
				if (current->map[i][j] == 'N' || current->map[i][j] == 'S' || current->map[i][j] == 'W' || current->map[i][j] == 'E')
				{
					//store the position of the player, and its type;
					v++;
				}
				else
					error_out("Unknown data type on the map!\n", 0);
			}
			// printf("i = %d\n", i);
			if (current->map[i][j] == '0')
			{
				printf("current->map[%d][%d] = %c\n", i, j + 1, current->map[i][j + 1]);
				printf("current->map[%d][%d] = %c\n", i, j - 1, current->map[i][j - 1]);
				printf("current->map[%d][%d] = %c\n", i + 1, j, current->map[i + 1][j]);
				printf("current->map[%d][%d] = %c\n", i - 1, j, current->map[i - 1][j]);
				if (current->map[i][j + 1] == ' ' || current->map[i][j - 1] == ' ' || current->map[i + 1][j] == ' ' || current->map[i - 1][j] == ' ')
					error_out("map structure near 0 is incorrect!\n", 0);
			}
			j++;
		}
		puts("rah hna");
		i++;
	}
	if (v == 0)
		error_out("There is no player on the map!\n", 0);
	while (current->map[i][j] && current->map[i][j] != '\n')
	{
		if (current->map[i][j] != '1' && current->map[i][j] != ' ')
			error_out("The walls have a hole :D!\n", 0);
		j++;
	}
}

int	last_value(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	// printf("last value = %d\n", i);
	return (i);
}