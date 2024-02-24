/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_e_w_s_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:09:10 by aouhbi            #+#    #+#             */
/*   Updated: 2024/02/04 18:04:34 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_line(char *line, t_data **data)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && (line[i + 2] == ' '
			|| line[i + 2] == '\t'))
		return (north_check(line, data), 0);
	else if (line[i] == 'S' && line[i + 1] == 'O' && (line[i + 2] == ' '
			|| line[i + 2] == '\t'))
		return (south_check(line, data), 0);
	else if (line[i] == 'W' && line[i + 1] == 'E' && (line[i + 2] == ' '
			|| line[i + 2] == '\t'))
		return (west_check(line, data), 0);
	else if (line[i] == 'E' && line[i + 1] == 'A' && (line[i + 2] == ' '
			|| line[i + 2] == '\t'))
		return (east_check(line, data), 0);
	else if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (floor_color_check(line, data), 0);
	else if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (ceiling_color_check(line, data), 0);
	else if (all_is_set(*data))
		return (error_out("Missing data\n", 0, *data), 1);
	else
		return (1);
}

void	north_check(char *line, t_data **data)
{
	char			**n_line;

	if ((*data)->north_tex != NULL)
		error_out("Duplicated identifier 'NO'\n", 0, *data);
	line = clean_tabs(line, *data);
	n_line = ft_split(line, ' ');
	if (n_line[1][ft_strlen(n_line[1]) - 1] == '\n')
		n_line[1][ft_strlen(n_line[1]) - 1] = '\0';
	if (n_line == NULL || n_line[2] != NULL)
	{
		if (n_line[2][0] != '\n')
			error_out("invalid file data\n", 0, *data);
		else if (n_line == NULL)
			error_out("invalid file data\n", 0, *data);
	}
	(*data)->north_tex = mlx_load_png(n_line[1]);
	if (!(*data)->north_tex)
		error_out("Error in texture file N", 0, *data);
}

void	south_check(char *line, t_data **data)
{
	char	**s_line;

	if ((*data)->south_tex != NULL)
		error_out("Duplicated identifier 'SO'\n", 0, *data);
	line = clean_tabs(line, *data);
	s_line = ft_split(line, ' ');
	if (s_line[1][ft_strlen(s_line[1]) - 1] == '\n')
		s_line[1][ft_strlen(s_line[1]) - 1] = '\0';
	if (s_line == NULL || s_line[2] != NULL)
	{
		if (s_line[2][0] != '\n')
			error_out("invalid file data\n", 0, *data);
		else if (s_line == NULL)
			error_out("invalid file data\n", 0, *data);
	}
	(*data)->south_tex = mlx_load_png(s_line[1]);
	if (!(*data)->south_tex)
		error_out("Error in texture file S", 0, *data);
}

void	west_check(char *line, t_data **data)
{
	char	**w_line;

	if ((*data)->west_tex != NULL)
		error_out("Duplicated identifier 'WE'\n", 0, *data);
	line = clean_tabs(line, *data);
	w_line = ft_split(line, ' ');
	if (w_line[1][ft_strlen(w_line[1]) - 1] == '\n')
		w_line[1][ft_strlen(w_line[1]) - 1] = '\0';
	if (w_line == NULL || w_line[2] != NULL)
	{
		if (w_line[2][0] != '\n')
			error_out("invalid file data\n", 0, *data);
		else if (w_line == NULL)
			error_out("invalid file data\n", 0, *data);
	}
	(*data)->west_tex = mlx_load_png(w_line[1]);
	if (!(*data)->west_tex)
		error_out("error in texture file W", 0, *data);
}

void	east_check(char *line, t_data **data)
{
	char	**e_line;

	if ((*data)->east_tex != NULL)
		error_out("Duplicated identifier 'EA'\n", 0, *data);
	line = clean_tabs(line, *data);
	e_line = ft_split(line, ' ');
	if (e_line[1][ft_strlen(e_line[1]) - 1] == '\n')
		e_line[1][ft_strlen(e_line[1]) - 1] = '\0';
	if (e_line == NULL || e_line[2] != NULL)
	{
		if (e_line[2][0] != '\n')
			error_out("invalid file data\n", 0, *data);
		else if (e_line == NULL)
			error_out("invalid file data\n", 0, *data);
	}
	(*data)->east_tex = mlx_load_png(e_line[1]);
	if (!(*data)->east_tex)
		error_out("Error in texture file E", 0, *data);
}
