/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:43:43 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/04 16:23:28 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	mlx_fill_rect(t_game *game, int width, int height, int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = game->player.p_x - game->player.dx;
	y = game->player.p_y - game->player.dy;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if ((x + j < WIDTH && y + i < HEIGHT) && (x + j > 0 && y + i > 0))
				mlx_put_pixel(game->mlx->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
