/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:44:07 by aouhbi            #+#    #+#             */
/*   Updated: 2024/01/22 08:33:47 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCING_HPP
#define PARCING_HPP


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "get_next_line.h"


typedef struct s_data
{
	int						north_fd;
	int						south_fd;
	int						west_fd;
	int						east_fd;
	struct s_floor			*floor_data;
	struct s_ceiling		*ceiling_data;
	char					**map;
}	t_data;


typedef struct s_floor
{
	int		R_f;
	int		G_f;
	int		B_f;
}	t_floor;

typedef struct s_ceiling
{
	int		R_c;
	int		G_c;
	int		B_c;
}	t_ceiling;

// ------------- parcing ---------------

size_t	ft_strlen(char *str);
char	**ft_split(char *s, char c);
int		ft_atoi(char *str);
int		ft_isdigit(int c);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strdup(char *s1);
void	*ft_memcpy(void *dst, void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);

void	set_struct(t_data *data);
void	parce_the_file(char	**f_name, t_data *data);
int		all_is_set(t_data *data);
int		check_line(char *line, t_data **data);
void	error_out(char *str, int v);
void	north_check(char *line, t_data **data);
void	south_check(char *line, t_data **data);
void	west_check(char *line, t_data **data);
void	east_check(char *line, t_data **data);
void	floor_color_check(char *line, t_data **data);
void	ceiling_color_check(char *line, t_data **data);
void	map_parcing(int fd, int size, char *line, t_data **data, size_t length);
void	print_map(t_data **data);
void	free_data(t_data *data);
void	free_all(t_data *data);
void	print_data(t_data *data);
int		number_check(char *str);
void	parce_and_save_map_line(char *line, t_data **data, int v, size_t length);
int		two_d_size(char *f_name, size_t *length);
char	*clean_tabs(char *line);
void	check_the_map(t_data **data);
int	last_value(char *str);


#endif