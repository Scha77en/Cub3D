/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:43:58 by aouhbi            #+#    #+#             */
/*   Updated: 2024/01/12 18:36:20 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

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
	data->floor_data->B_f = -1;
	data->floor_data->G_f = -1;
	data->floor_data->B_f = -1;
	data->ceiling_data->B_c = -1;
	data->ceiling_data->G_c = -1;
	data->ceiling_data->B_c = -1;
}

int	main(int argc, char	*argv[])
{
	size_t		i;
	t_data		data;

	set_struct(&data);
	i = 0;
	if (argc != 2)
		write(2, "Error: Wrong Number Of Arguments!\n", 34);
	else
	{
		i = ft_strlen(argv[1]) - 1;
		if (argv[1][i] == 'b' && argv[1][i - 1] == 'u' && argv[1][i - 2] == 'c'
				&& argv[1][i - 3] == '.')
			parce_the_file(argv, &data);
		else
			write (2, "Error: Wrong File Format. Format must be '*.cub'\n", 49);
	}
}

void	parce_the_file(char	**f_name, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(f_name[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] == '\n');
			continue ;
		check_line(line, data);
		free(line);
	}
	puts("format is correct");
}

void	check_line(char *line, t_data *data)
{
	int		i;

	i = 0;
	if (line[i] == 'N' && line[i + 1] == 'O' && (line[2] == ' ' || line[2] == '\t'))
		north_check(line, data);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[2] == ' ' || line[2] == '\t')
		south_check(line, data);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[2] == ' ' || line[2] == '\t')
		west_check(line, data);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[2] == ' ' || line[2] == '\t')
		east_check(line, data);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		floor_color_check(line, data);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		ceiling_color_check(line, data);
	else
		error_out("missing or duplicated element in the file\n", 0);
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

void	north_check(char *line, t_data *data)
{
	char	**n_line;

	if (data->north_fd != -1)
		error_out("Duplicated identifier 'NO'\n", 0);
	n_line = ft_split(line, ' ');
	if (n_line == NULL || n_line[2] != NULL)
		error_out("invalid file data\n", 0);
	else if (line[1] == '.' && line [2] == '/' && line[3])
		data->north_fd = open(n_line[1], O_RDONLY);
	if (data->north_fd == -1)
		error_out("open", 1);
}

void	south_check(char *line, t_data *data)
{
	char	**s_line;

	if (data->south_fd != -1)
		error_out("Duplicated identifier 'SO'\n", 0);
	s_line = ft_split(line, ' ');
	if (s_line == NULL || s_line[2] != NULL)
		error_out("invalid file data\n", 0);
	else if (line[1] == '.' && line [2] == '/' && line[3])
		data->south_fd = open(s_line[1], O_RDONLY);
	if (data->south_fd == -1)
		error_out("open", 1);
}

void	west_check(char *line, t_data *data)
{
	char	**w_line;

	if (data->west_fd != -1)
		error_out("Duplicated identifier 'WE'\n", 0);
	w_line = ft_split(line, ' ');
	if (w_line == NULL || w_line[2] != NULL)
		error_out("invalid file data\n", 0);
	else if (line[1] == '.' && line [2] == '/' && line[3])
		data->west_fd = open(w_line[1], O_RDONLY);
	if (data->west_fd == -1)
		error_out("open", 1);
}

void	east_check(char *line, t_data *data)
{
	char	**e_line;

	if (data->east_fd != -1)
		error_out("Duplicated identifier 'EA'\n", 0);
	e_line = ft_split(line, ' ');
	if (e_line == NULL || e_line[2] != NULL)
		error_out("invalid file data\n", 0);
	else if (line[1] == '.' && line [2] == '/' && line[3])
		data->east_fd = open(e_line[1], O_RDONLY);
	if (data->east_fd == -1)
		error_out("open", 1);
}

void	floor_color_check(char *line, t_data *data)
{
	char	**f_line;
	char	**colors;

	if (data->floor_data->R_f != -1 || data->floor_data->G_f != -1 || data->floor_data->B_f != -1)
		error_out("Duplicated identifier 'F'\n", 0);
	f_line = ft_split(line, ' ');
	if (f_line == NULL || f_line[2] != NULL)
		error_out("invalid file data\n", 0);
	colors = ft_split(f_line[1], ',');
	if (colors == NULL || colors[3] != NULL)
		error_out("invalid file data\n", 0);
	else
	{
		if (ft_atoi(colors[0]) >= 0 && ft_atoi(colors[0]) <= 255)
			data->floor_data->R_f = ft_atoi(colors[0]);
		else
			error_out("Floor Red color is out of range", 0);
		if (ft_atoi(colors[1]) >= 0 && ft_atoi(colors[1]) <= 255)
			data->floor_data->G_f = ft_atoi(colors[1]);
		else
			error_out("Floor Green color is out of range", 0);
		if (ft_atoi(colors[2]) >= 0 && ft_atoi(colors[2]) <= 255)
			data->floor_data->B_f = ft_atoi(colors[2]);
		else
			error_out("Floor Blue color is out of range", 0);
	}
}

void	ceiling_color_check(char *line, t_data *data)
{
	char	**c_line;
	char	**colors;

	if (data->ceiling_data->R_c != -1 || data->ceiling_data->G_c != -1 || data->ceiling_data->B_c != -1)
		error_out("Duplicated identifier 'C'\n", 0);
	c_line = ft_split(line, ' ');
	if (c_line == NULL || c_line[2] != NULL)
		error_out("invalid file data\n", 0);
	colors = ft_split(c_line[1], ',');
	if (colors == NULL || colors[3] != NULL)
		error_out("invalid file data\n", 0);
	else
	{
		if (ft_atoi(colors[0]) >= 0 && ft_atoi(colors[0]) <= 255)
			data->ceiling_data->R_c = ft_atoi(colors[0]);
		else
			error_out("Ceiling Red color is out of range", 0);
		if (ft_atoi(colors[1]) >= 0 && ft_atoi(colors[1]) <= 255)
			data->ceiling_data->G_c = ft_atoi(colors[1]);
		else
			error_out("Ceiling Green color is out of range", 0);
		if (ft_atoi(colors[2]) >= 0 && ft_atoi(colors[2]) <= 255)
			data->ceiling_data->B_c = ft_atoi(colors[2]);
		else
			error_out("Ceiling Blue color is out of range", 0);
	}
}
