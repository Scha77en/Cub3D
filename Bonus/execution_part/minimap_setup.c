/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:33:11 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/04 18:16:04 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_miniplayer(t_game *game, double x, double y, int color)
{
	int	i;
	int	j;

	i = y;
	while (i < y + 3)
	{
		j = x;
		while (j < x + 3)
		{
			if (i >= 0 && j >= 0 && i < 180 && j < 180)
				mlx_put_pixel(game->mlx->img, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_square(t_game *game, double x, double y, int color)
{
	int	i;
	int	j;

	i = y;
	while (i < y + TILE_SIZE)
	{
		j = x;
		while (j < x + TILE_SIZE)
		{
			if (i >= 0 && j >= 0 && i < 180 && j < 180)
				mlx_put_pixel(game->mlx->img, j, i, color);
			j++;
		}
		i++;
	}
}

void	minimap_setup(t_game *game)
{
	int		i;
	int		j;
	double	rot_angle;

	game->player.dx = game->player.p_x - 120;
	game->player.dy = game->player.p_y - 120;
	i = 0;
	j = 0;
	rendring_mini_map(game, i, j);
	rot_angle = normalizeangle(game->player.rotation_angle);
	mlx_fill_rect(game, 3, 3, ft_pixel(255, 0, 0, 255));
}

void	rendring_mini_map(t_game *game, int i, int j)
{
	while (i < game->data->map_height)
	{
		j = 0;
		while (j < game->data->map_width)
		{
			if (game->data->map[i][j] == '1')
				draw_square(game, (i * TILE_SIZE) - game->player.dy, \
					(j * TILE_SIZE) - game->player.dx, 0x00FFFFFF);
			else if (game->data->map[i][j] == '0' \
				|| game->data->map[i][j] == 'N' \
				|| game->data->map[i][j] == 'S' || game->data->map[i][j] == 'E' \
				|| game->data->map[i][j] == 'W')
				draw_square(game, (i * TILE_SIZE) - game->player.dy, \
					(j * TILE_SIZE) - game->player.dx, 0x00000000);
			j++;
		}
		i++;
	}
}
