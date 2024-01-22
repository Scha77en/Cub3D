/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 06:18:34 by aouhbi            #+#    #+#             */
/*   Updated: 2024/01/21 08:47:04 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

char	*get_the_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = (char *) malloc(sizeof(*line) * (i + 2));
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
	{
		free(save);
		return (NULL);
	}
	new_save = (char *) malloc(sizeof(*new_save) * (ft_strlen(save) - i + 1));
	if (!new_save)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	free(save);
	return (new_save);
}

char	*read_and_save(int fd, char *save)
{
	char	*buff;
	int		readed;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(*buff));
	if (!buff)
		return (NULL);
	readed = 1;
	while (!ft_strchr(save, '\n') && readed)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(save);
			free(buff);
			return (NULL);
		}
		buff[readed] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
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

// int	main(void)
// {
// 	int		fd;
// 	int		fd2;

// 	fd = open("test.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);

// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd2));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd2));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd2));

// 	close(fd);
// 	close(fd2);
// 	return (0);
// }
