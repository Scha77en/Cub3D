/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parcing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 06:22:58 by aouhbi            #+#    #+#             */
/*   Updated: 2024/02/04 18:30:33 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	map_parcing(int fd, char *line, t_game **game, size_t width)
{
	int		i;
	int		k;

	i = 1;
	parce_and_save_map_line(line, game, 0, width);
	while (1)
	{
		k = 0;
		line = get_next_line(fd);
		if (line == NULL)
		{
			break ;
		}
		while (line[k] == ' ' || line[k] == '\t')
			k++;
		if (line[k] == '\n' || line[k] == '\0')
			break ;
		parce_and_save_map_line(line, game, i, width);
		i++;
	}
	(*game)->data->map[i] = NULL;
	check_the_map(game);
}

void	parce_and_save_map_line(char *line, t_game **game, int v, size_t length)
{
	ssize_t		i;
	ssize_t		j;
	t_data		*current;

	i = 0;
	j = 0;
	current = (*game)->data;
	line = clean_tabs(line, (*game)->data);
	current->map[v] = ft_calloc(length + 1, sizeof(char));
	while (line[i] && line[i] != '\n')
		current->map[v][j++] = line[i++];
	while ((size_t)j < length)
	{
		current->map[v][j] = ' ';
		j++;
	}
	current->map[v][j] = '\0';
}

int	two_d_size(char *f_name, size_t *length, t_data *data)
{
	int		i;
	int		x;

	*length = 0;
	x = 0;
	data->fd1 = open(f_name, O_RDONLY);
	if (data->fd1 < 0)
		error_out("open", 1, data);
	loop_six_elements(data->fd1, length, data);
	i = 1;
	x = looping_the_rest(data->fd1, length, x, i);
	if (x == -1)
		error_out("The map is not valid!\n", 0, data);
	return (x);
}

void	check_the_map(t_game **game)
{
	int		i;
	int		j;
	int		v;
	int		k;
	t_data	*current;

	j = 0;
	v = 0;
	k = 0;
	current = (*game)->data;
	front_wall_check(current);
	i = 1;
	while (current->map[i + 1])
	{
		in_between_wall_check(game, current, i, &v);
		i++;
	}
	if (v == 0)
		error_out("There is no player on the map!\n", 0, (*game)->data);
	while (current->map[i][j] && current->map[i][j] != '\n')
	{
		if (current->map[i][j] != '1' && current->map[i][j] != ' ')
			error_out("The walls have a hole :D!\n", 0, (*game)->data);
		j++;
	}
}

void	store_position(t_game **game, int i, int j)
{
	(*game)->player.p_x = (j * TILE_SIZE) + (TILE_SIZE / 2);
	(*game)->player.p_y = (i * TILE_SIZE) + (TILE_SIZE / 2);
	(*game)->player.position_player = (*game)->data->map[i][j];
}
