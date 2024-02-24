/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 06:18:34 by aouhbi            #+#    #+#             */
/*   Updated: 2024/02/03 03:22:20 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*get_the_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = (char *) my_malloc(sizeof(*line), (i + 2), 1);
	if (!line)
		return (NULL);
	i = -1;
	while (save[++i] && save[i] != '\n')
		line[i] = save[i];
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*clean_save(char *save)
{
	int		i;
	int		j;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return (NULL);
	new_save = (char *) my_malloc(sizeof(*new_save),
			(ft_strlen(save) - i + 1), 1);
	if (!new_save)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	return (new_save);
}

char	*read_and_save(int fd, char *save)
{
	char	*buff;
	int		readed;

	buff = my_malloc((BUFFER_SIZE + 1), sizeof(*buff), 1);
	if (!buff)
		return (NULL);
	readed = 1;
	while (!ft_strchr(save, '\n') && readed)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			return (NULL);
		}
		buff[readed] = '\0';
		save = ft_strjoin(save, buff);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	save[fd] = read_and_save(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = get_the_line(save[fd]);
	save[fd] = clean_save(save[fd]);
	return (line);
}
