/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:43:58 by aouhbi            #+#    #+#             */
/*   Updated: 2024/01/20 18:46:46 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

int	main(int argc, char	*argv[])
{
	size_t		i;
	t_data		*data;

	data = malloc(sizeof(t_data));
	data->floor_data = malloc(sizeof(t_floor));
	data->ceiling_data = malloc(sizeof(t_ceiling));
	data->map = NULL;
	set_struct(data);
	i = 0;
	if (argc != 2)
		write(2, "Error: Wrong Number Of Arguments!\n", 34);
	else
	{
		i = ft_strlen(argv[1]) - 1;
		if (argv[1][i] == 'b' && argv[1][i - 1] == 'u' && argv[1][i - 2] == 'c'
				&& argv[1][i - 3] == '.')
			parce_the_file(argv, data);
		else
			write (2, "Error: Wrong File Format. Format must be '*.cub'\n", 49);
	}
}

size_t	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	set_struct(t_data *data)
{
	data->north_fd = -1;
	data->south_fd = -1;
	data->west_fd = -1;
	data->east_fd = -1;
	data->floor_data->R_f = -1;
	data->floor_data->G_f = -1;
	data->floor_data->B_f = -1;
	data->ceiling_data->R_c = -1;
	data->ceiling_data->G_c = -1;
	data->ceiling_data->B_c = -1;
}

// file_parcing

void	parce_the_file(char	**f_name, t_data *data)
{
	int		fd;
	char	*line;
	int		v;
	int		size;

	size = 0;
	v = 0;
	fd = open(f_name[1], O_RDONLY);
	if (fd == -1)
		error_out("open", 1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		v = check_line(line, &data);
		if (v == 1)
			break ;
		free(line);
	}
	printf("line = %s\n", line);
	printf("v = %d\n", v);
	// size = two_d_size(f_name[1]);
	printf("size = %d\n", size);
	if (v == 1)
		map_parcing(fd, size, line, &data);
	print_data(data);
	print_map(&data);
}

int	all_is_set(t_data *data)
{
	if (data->north_fd != -1 && data->south_fd != -1 && data->west_fd != -1 && data->east_fd != -1
		&& data->floor_data->B_f != 1 && data->floor_data->G_f != -1 && data->floor_data->B_f != 1 && data->ceiling_data->B_c != 1
		&& data->ceiling_data->G_c != -1 && data->ceiling_data->B_c != 1)
		return (0);
	else
		return (1);
}

int	check_line(char *line, t_data **data)
{
	int		i;

	i = 0;
	if (line[i] == 'N' && line[i + 1] == 'O' && (line[2] == ' ' || line[2] == '\t'))
		return (north_check(line, data), 0);
	else if (line[i] == 'S' && line[i + 1] == 'O' && (line[2] == ' ' || line[2] == '\t'))
		return (south_check(line, data), 0);
	else if (line[i] == 'W' && line[i + 1] == 'E' && (line[2] == ' ' || line[2] == '\t'))
		return (west_check(line, data), 0);
	else if (line[i] == 'E' && line[i + 1] == 'A' && (line[2] == ' ' || line[2] == '\t'))
		return (east_check(line, data), 0);
	else if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (floor_color_check(line, data), 0);
	else if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (ceiling_color_check(line, data), 0);
	else if (all_is_set(*data))
		return (error_out("Missing data\n", 0), 1);
	else
		return (1);
}

void	error_out(char *str, int v)
{
	write(2, "Error\n", 6);
	if (v == 0)
		write(2, str, ft_strlen(str));
	else
		perror(str);
	exit(EXIT_FAILURE);
}

void	north_check(char *line, t_data **data)
{
	char	**n_line;

	if ((*data)->north_fd != -1)
		error_out("Duplicated identifier 'NO'\n", 0);
	n_line = ft_split(line, ' ');
	printf("n_line[1] = %s\n", n_line[1]);
	n_line[1][ft_strlen(n_line[1]) - 1] = '\0';
	if (n_line == NULL || n_line[2] != NULL)
		error_out("invalid file data\n", 0);
	printf("north_fd = %d\n", (*data)->north_fd);
	(*data)->north_fd = open(n_line[1], O_RDONLY);
	printf("north_fd = %d\n", (*data)->north_fd);
	if ((*data)->north_fd == -1)
		error_out("open", 1);
}

void	south_check(char *line, t_data **data)
{
	char	**s_line;

	if ((*data)->south_fd != -1)
		error_out("Duplicated identifier 'SO'\n", 0);
	s_line = ft_split(line, ' ');
	printf("s_line[1] = %s\n", s_line[1]);
	s_line[1][ft_strlen(s_line[1]) - 1] = '\0';
	if (s_line == NULL || s_line[2] != NULL)
		error_out("invalid file data\n", 0);
	(*data)->south_fd = open(s_line[1], O_RDONLY);
	if ((*data)->south_fd == -1)
		error_out("open", 1);
	printf("south_fd = %d\n", (*data)->south_fd);
}

void	west_check(char *line, t_data **data)
{
	char	**w_line;

	if ((*data)->west_fd != -1)
		error_out("Duplicated identifier 'WE'\n", 0);
	w_line = ft_split(line, ' ');
	printf("w_line[1] = %s\n", w_line[1]);
	w_line[1][ft_strlen(w_line[1]) - 1] = '\0';
	if (w_line == NULL || w_line[2] != NULL)
		error_out("invalid file data\n", 0);
	(*data)->west_fd = open(w_line[1], O_RDONLY);
	if ((*data)->west_fd == -1)
		error_out("open", 1);
	printf("west_fd = %d\n", (*data)->west_fd);
}

void	east_check(char *line, t_data **data)
{
	char	**e_line;

	if ((*data)->east_fd != -1)
		error_out("Duplicated identifier 'EA'\n", 0);
	e_line = ft_split(line, ' ');
	printf("e_line[1] = %s\n", e_line[1]);
	e_line[1][ft_strlen(e_line[1]) - 1] = '\0';
	if (e_line == NULL || e_line[2] != NULL)
		error_out("invalid file data\n", 0);
	(*data)->east_fd = open(e_line[1], O_RDONLY);
	if ((*data)->east_fd == -1)
		error_out("open", 1);
	printf("east_fd = %d\n", (*data)->east_fd);
}

void	floor_color_check(char *line, t_data **data)
{
	char	**f_line;
	char	**colors;

	if ((*data)->floor_data->R_f != -1 || (*data)->floor_data->G_f != -1 || (*data)->floor_data->B_f != -1)
		error_out("Duplicated identifier 'F'\n", 0);
	f_line = ft_split(line, ' ');
	if (f_line == NULL || f_line[2] != NULL)
		error_out("invalid file data\n", 0);
	colors = ft_split(f_line[1], ',');
	if (colors == NULL || colors[3] != NULL)
		error_out("invalid file data\n", 0);
	if (colors[0] == NULL || colors[1] == NULL || colors[2] == NULL)
		error_out("invalid Floor data\n", 0);
	if (number_check(colors[0]) == 0 || number_check(colors[1]) == 0 || number_check(colors[2]) == 0)
		error_out("invalid Floor data\n", 0);
	(*data)->floor_data->R_f = ft_atoi(colors[0]);
	(*data)->floor_data->G_f = ft_atoi(colors[1]);
	(*data)->floor_data->B_f = ft_atoi(colors[2]);
	printf("R_f = %d\n", (*data)->floor_data->R_f);
	printf("G_f = %d\n", (*data)->floor_data->G_f);
	printf("B_f = %d\n", (*data)->floor_data->B_f);
}

void	ceiling_color_check(char *line, t_data **data)
{
	char	**c_line;
	char	**colors;

	if ((*data)->ceiling_data->R_c != -1 || (*data)->ceiling_data->G_c != -1 || (*data)->ceiling_data->B_c != -1)
		error_out("Duplicated identifier 'C'\n", 0);
	c_line = ft_split(line, ' ');
	if (c_line == NULL || c_line[2] != NULL)
		error_out("invalid file data\n", 0);
	colors = ft_split(c_line[1], ',');
	if (colors == NULL || colors[3] != NULL)
		error_out("invalid file data\n", 0);
	if (colors[0] == NULL || colors[1] == NULL || colors[2] == NULL)
		error_out("invalid Ceiling data\n", 0);
	if (number_check(colors[0]) == 0 || number_check(colors[1]) == 0 || number_check(colors[2]) == 0)
		error_out("invalid Ceiling data\n", 0);
	(*data)->ceiling_data->R_c = ft_atoi(colors[0]);
	(*data)->ceiling_data->G_c = ft_atoi(colors[1]);
	(*data)->ceiling_data->B_c = ft_atoi(colors[2]);
	printf("R_c = %d\n", (*data)->ceiling_data->R_c);
	printf("G_c = %d\n", (*data)->ceiling_data->G_c);
	printf("B_c = %d\n", (*data)->ceiling_data->B_c);
}

void	print_map(t_data **data)
{
	int		i;

	i = 0;
	while ((*data)->map[i])
	{
		printf("map[%d] == %s\n", i, (*data)->map[i]);
		i++;
	}
}

void	free_data(t_data *data)
{
	int		i;

	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	free(data->floor_data);
	free(data->ceiling_data);
}

void	free_all(t_data *data)
{
	free_data(data);
	close(data->north_fd);
	close(data->south_fd);
	close(data->west_fd);
	close(data->east_fd);
}

void	print_data(t_data *data)
{
	printf("north_fd = %d\n", data->north_fd);
	printf("south_fd = %d\n", data->south_fd);
	printf("west_fd = %d\n", data->west_fd);
	printf("east_fd = %d\n", data->east_fd);
	printf("R_f = %d\n", data->floor_data->R_f);
	printf("G_f = %d\n", data->floor_data->G_f);
	printf("B_f = %d\n", data->floor_data->B_f);
	printf("R_c = %d\n", data->ceiling_data->R_c);
	printf("G_c = %d\n", data->ceiling_data->G_c);
	printf("B_c = %d\n", data->ceiling_data->B_c);
}
