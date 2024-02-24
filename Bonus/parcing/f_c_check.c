/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_c_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:10:53 by aouhbi            #+#    #+#             */
/*   Updated: 2024/02/04 18:37:59 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	floor_color_check(char *line, t_data **data)
{
	char	**f_line;
	char	**colors;

	if ((*data)->floor_data->r_f != -1 || (*data)->floor_data->g_f != -1
		|| (*data)->floor_data->b_f != -1)
		error_out("Duplicated identifier 'F'\n", 0, (*data));
	line = clean_tabs(line, *data);
	f_line = ft_split(line, ' ');
	colors = split_and_join(f_line, *data);
	if (colors[0] == NULL || colors[1] == NULL || colors[2] == NULL)
		error_out("invalid Floor data\n", 0, (*data));
	colors[2][ft_strlen(colors[2]) - 1] = '\0';
	if (colors == NULL || colors[3] != NULL || colors[0][0] == '\0'
		|| colors[1][0] == '\0' || colors[2][0] == '\0')
		error_out("invalid Floor data\n", 0, (*data));
	if (number_check(colors[0], *data) == 0
		|| number_check(colors[1], *data) == 0
		|| number_check(colors[2], *data) == 0)
		error_out("invalid Floor data\n", 0, (*data));
	(*data)->floor_data->r_f = ft_atoi(colors[0]);
	(*data)->floor_data->g_f = ft_atoi(colors[1]);
	(*data)->floor_data->b_f = ft_atoi(colors[2]);
}

void	ceiling_color_check(char *line, t_data **data)
{
	char	**c_line;
	char	**colors;

	if ((*data)->ceiling_data->r_c != -1 || (*data)->ceiling_data->g_c != -1
		|| (*data)->ceiling_data->b_c != -1)
		error_out("Duplicated identifier 'C'\n", 0, (*data));
	line = clean_tabs(line, *data);
	c_line = ft_split(line, ' ');
	colors = split_and_join(c_line, *data);
	if (colors[0] == NULL || colors[1] == NULL || colors[2] == NULL)
		error_out("invalid Ceiling data\n", 0, (*data));
	colors[2][ft_strlen(colors[2]) - 1] = '\0';
	if (colors == NULL || colors[3] != NULL || colors[0][0] == '\0'
		|| colors[1][0] == '\0' || colors[2][0] == '\0')
		error_out("invalid Ceiling data\n", 0, (*data));
	if (number_check(colors[0], *data) == 0
		|| number_check(colors[1], *data) == 0
		|| number_check(colors[2], *data) == 0)
		error_out("invalid Ceiling data\n", 0, *data);
	(*data)->ceiling_data->r_c = ft_atoi(colors[0]);
	(*data)->ceiling_data->g_c = ft_atoi(colors[1]);
	(*data)->ceiling_data->b_c = ft_atoi(colors[2]);
}

int	all_is_set(t_data *data)
{
	if (data->north_tex != NULL && data->south_tex != NULL && data->west_tex
		!= NULL && data->east_tex != NULL && data->floor_data->r_f != -1
		&& data->floor_data->g_f != -1 && data->floor_data->b_f != -1
		&& data->ceiling_data->r_c != -1 && data->ceiling_data->g_c != -1
		&& data->ceiling_data->b_c != -1)
		return (0);
	else
		return (1);
}
