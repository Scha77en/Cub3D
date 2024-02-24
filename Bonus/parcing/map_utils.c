/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:28:44 by aouhbi            #+#    #+#             */
/*   Updated: 2024/02/04 18:33:11 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	loop_six_elements(int fd, size_t *length, t_data *data)
{
	int		i;
	int		k;
	char	*line;

	i = 0;
	while (i <= 6)
	{
		k = 0;
		line = get_next_line(fd);
		if (line == NULL)
			error_out("data is missing!\n", 0, data);
		while (line[k] == ' ' || line[k] == '\t')
			k++;
		if (line[k] == '\n')
			continue ;
		else if (line[k] == '\0')
			error_out("map is missing!\n", 0, data);
		i++;
	}
	*length = ft_strlen(line);
	if (line[ft_strlen(line) - 1] == '\n')
		(*length)--;
}

int	looping_the_rest(int fd, size_t *length, int x, int i)
{
	int		k;
	char	*line;

	while (1)
	{
		k = 0;
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\0')
			break ;
		while (line[k] == ' ' || line[k] == '\t')
			k++;
		if (line[k] == '\n')
		{
			x = 1;
			continue ;
		}
		if ((*length) < ft_strlen(line))
			(*length) = ft_strlen(line);
		else if (line[k] != '\n' && x == 1 && line[k] != '\0')
			return (-1);
		else if (line[k] != '\n' && x == 1 && line[k] == '\0')
			break ;
		i++;
	}
	return (i);
}

void	front_wall_check(t_data *current)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (current->map[i] && current->map[i][j] && current->map[i][j] != '\n')
	{
		if (current->map[i][j] != '1' && current->map[i][j] != ' ')
			error_out("The walls have a hole :D!\n", 0, current);
		j++;
	}
	if (current->map[1] == NULL || current->map[2] == NULL)
		error_out("Invalid map!\n", 0, current);
}

void	in_between_wall_check(t_game **game, t_data *current, int i, int *v)
{
	int		j;
	int		k;
	int		a;

	j = 0;
	k = 0;
	a = 0;
	while (current->map[i][j] && current->map[i][j] != '\n')
	{
		if (check_spaces(current->map[i][j], &k, &j) == 1)
			continue ;
		more_checks(game, i, j, v);
		if ((current->map[i][k] != '1'
			|| current->map[i][last_value(current->map[i])] != '1') && a == 0)
			error_out("The borders are brocken!\n", 0, current);
		if (current->map[i][j] == '0')
		{
			if (current->map[i][j + 1] == ' ' || current->map[i][j - 1] == ' '
			|| current->map[i + 1][j] == ' ' || current->map[i - 1][j] == ' ')
				error_out("map structure near 0 is incorrect!\n", 0, current);
		}
		j++;
		a++;
	}
}

void	more_checks(t_game **game, int i, int j, int *v)
{
	t_data	*current;

	current = (*game)->data;
	if (current->map[i][j] != '1' && current->map[i][j]
		!= '0' && current->map[i][j] != ' ')
	{
		if (current->map[i][j] == 'N' || current->map[i][j] == 'S'
			|| current->map[i][j] == 'W' || current->map[i][j] == 'E')
		{
			if (current->map[i][j + 1] == ' ' || current->map[i][j - 1] == ' '
			|| current->map[i + 1][j] == ' ' || current->map[i - 1][j] == ' ')
				error_out("map structure near NSWE is incorrect!\n", 0,
					current);
			if (*v > 0)
				error_out("There is more than one player on the map!\n", 0,
					current);
			store_position(game, i, j);
			(*v)++;
		}
		else
			error_out("Unknown data type on the map!\n", 0, current);
	}
}
