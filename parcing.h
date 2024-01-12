/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:44:07 by aouhbi            #+#    #+#             */
/*   Updated: 2024/01/12 18:22:41 by aouhbi           ###   ########.fr       */
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


typedef struct s_data
{
	int						north_fd;
	int						south_fd;
	int						west_fd;
	int						east_fd;
	struct s_floor			*floor_data;
	struct s_ceiling		*ceiling_data;
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

void	parce_the_file(char	**f_name, t_data *data);
size_t	ft_strlen(char *str);


#endif