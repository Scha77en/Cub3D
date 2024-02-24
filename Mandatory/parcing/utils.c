/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:12:33 by aouhbi            #+#    #+#             */
/*   Updated: 2024/02/04 17:58:56 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

size_t	ft_strlen(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**split_and_join(char **f_line, t_data *data)
{
	int		i;
	int		counter;
	char	*new_line;
	char	**data_line;

	new_line = NULL;
	i = 1;
	while (f_line[i])
	{
		new_line = ft_strjoin(new_line, f_line[i]);
		i++;
	}
	i = 0;
	counter = 0;
	while (new_line[i])
	{
		if (new_line[i] == ',')
			counter++;
		i++;
	}
	if (counter != 2)
		error_out("invalid data\n", 0, data);
	data_line = ft_split(new_line, ',');
	return (data_line);
}

char	*clean_tabs(char *line, t_data *data)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = my_malloc(sizeof(char), (ft_strlen(line) + 1), 1);
	if (new_line == NULL)
		error_out("malloc", 1, data);
	while (line[i])
	{
		if (line[i] == '\t')
		{
			new_line[j] = ' ';
			j++;
		}
		else
		{
			new_line[j] = line[i];
			j++;
		}
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}

void	print_map(t_data **data)
{
	int		i;

	i = 0;
	while ((*data)->map[i])
	{
		printf("map[%d]   ==   [%s]\n", i, (*data)->map[i]);
		i++;
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
	return (i);
}
