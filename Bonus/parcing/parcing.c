/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:43:58 by aouhbi            #+#    #+#             */
/*   Updated: 2024/02/04 18:20:09 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	setting_data_1(t_game **game)
{
	if (*game == NULL)
		error_out("malloc", 1, NULL);
	(*game)->data = my_malloc(sizeof(t_data), 1, 1);
	if ((*game)->data == NULL)
		error_out("malloc", 1, NULL);
	(*game)->data->floor_data = my_malloc(sizeof(t_floor), 1, 1);
	if ((*game)->data->floor_data == NULL)
		error_out("malloc", 1, NULL);
	(*game)->data->ceiling_data = my_malloc(sizeof(t_ceiling), 1, 1);
	if ((*game)->data->ceiling_data == NULL)
		error_out("malloc", 1, NULL);
	(*game)->mlx = my_malloc(sizeof(t_mlx), 1, 1);
	(*game)->data->map = NULL;
	(*game)->data->north_tex = NULL;
	(*game)->data->south_tex = NULL;
	(*game)->data->west_tex = NULL;
	(*game)->data->east_tex = NULL;
	(*game)->data->floor_data->r_f = -1;
	(*game)->data->floor_data->g_f = -1;
	(*game)->data->floor_data->b_f = -1;
	(*game)->data->ceiling_data->r_c = -1;
	(*game)->data->ceiling_data->g_c = -1;
	(*game)->data->ceiling_data->b_c = -1;
	(*game)->data->fd1 = -1;
	(*game)->data->fd2 = -1;
}

void	parce_the_file(char	**f_name, t_game **game)
{
	char	*line;
	int		v;
	int		size;
	size_t	length;

	size = two_d_size(f_name[1], &length, (*game)->data);
	v = 0;
	(*game)->data->fd2 = open(f_name[1], O_RDONLY);
	if ((*game)->data->fd2 == -1)
		error_out("open", 1, (*game)->data);
	loop_over_the_map((*game)->data->fd2, &line, game, &v);
	assigne_hight_and_width(game, size, length);
	if (v == 1)
		map_parcing((*game)->data->fd2, line, game, length);
}

void	error_out(char *str, int v, t_data *data)
{
	if (data != NULL)
	{
		if (data->fd1 != -1)
			close(data->fd1);
		if (data->fd2 != -1)
			close(data->fd2);
	}
	write(2, "Error\n", 6);
	if (v == 0)
		write(2, str, ft_strlen(str));
	else
		perror(str);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	loop_over_the_map(int fd, char **line, t_game **game, int *v)
{
	int		i;

	while (1)
	{
		i = 0;
		*line = get_next_line(fd);
		if (*line == NULL)
			break ;
		while ((*line)[i] == ' ' || (*line)[i] == '\t')
			i++;
		if ((*line)[i] == '\n')
		{
			free((*line));
			continue ;
		}
		*v = check_line(*line, &(*game)->data);
		if (*v == 1)
			break ;
	}
}

void	assigne_hight_and_width(t_game **game, int size, size_t length)
{
	(*game)->data->map_height = size;
	(*game)->data->map_width = length;
	(*game)->data->map = my_malloc(sizeof(char *), size + 1, 1);
}
