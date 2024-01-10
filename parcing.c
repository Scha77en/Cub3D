/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:43:58 by aouhbi            #+#    #+#             */
/*   Updated: 2024/01/10 16:43:03 by aouhbi           ###   ########.fr       */
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

int	main(int argc, char	*argv[])
{
	size_t		i;

	i = 0;
	if (argc != 2)
		write(2, "Error: Wrong Number Of Arguments!\n", 34);
	else
	{
		i = ft_strlen(argv[1]) - 1;
		if (argv[1][i] == 'b' && argv[1][i - 1] == 'u' && argv[1][i - 2] == 'c'
				&& argv[1][i - 3] == '.')
			parce_the_file(argv);
		else
			write (2, "Error: Wrong File Format. Format must be '*.cub'\n", 49);
	}
}

void	parce_the_file(char	**f_name)
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
		check_line(line);
		free(line);
	}
	puts("format is correct");
}