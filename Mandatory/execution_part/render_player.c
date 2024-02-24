/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:02:52 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/03 09:38:42 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	maphaswallat_movement(t_game *game, float x, float y)
{
	int	mapgridindex_x;
	int	mapgridindex_y;
	int	mapgridindex_x_old;
	int	mapgridindex_y_old;

	if (x < 0 || floor(x / TILE_SIZE) > game->data->map_width || \
		y < 0 || floor(y / TILE_SIZE) >= game->data->map_height)
		return (TRUE);
	mapgridindex_x = (int)(x / TILE_SIZE);
	mapgridindex_y = (int)(y / TILE_SIZE);
	mapgridindex_x_old = (int)(game->player.p_x / TILE_SIZE);
	mapgridindex_y_old = (int)(game->player.p_y / TILE_SIZE);
	if (mapgridindex_y < HEIGHT && mapgridindex_x < WIDTH && \
		game->data->map[mapgridindex_y][mapgridindex_x] == '1')
		return (TRUE);
	else if (mapgridindex_y_old < HEIGHT && mapgridindex_x < WIDTH && \
		game->data->map[mapgridindex_y_old][mapgridindex_x] == '1')
		return (TRUE);
	else if (mapgridindex_y < HEIGHT && mapgridindex_x_old < WIDTH && \
		game->data->map[mapgridindex_y][mapgridindex_x_old] == '1')
		return (TRUE);
	else
		return (FALSE);
}

bool	maphaswallat_rays(t_game *game, float x, float y)
{
	int	mapgridindex_x;
	int	mapgridindex_y;

	if (x < 0 || floor(x / TILE_SIZE) > game->data->map_width || \
		y < 0 || floor(y / TILE_SIZE) >= game->data->map_height)
		return (TRUE);
	mapgridindex_x = (int)(x / TILE_SIZE);
	mapgridindex_y = (int)(y / TILE_SIZE);
	if (mapgridindex_y < HEIGHT && mapgridindex_x < WIDTH && \
		game->data->map[mapgridindex_y][mapgridindex_x] == '1')
		return (TRUE);
	else
		return (FALSE);
}

void	check_movement(t_game *game, float newplayerx, float newplayery)
{
	if (!maphaswallat_movement(game, newplayerx, newplayery))
	{
		game->player.p_x = newplayerx;
		game->player.p_y = newplayery;
	}
}

void	moveplayer(t_game *game, float movestep, float deltaTime)
{
	float	newplayerx;
	float	newplayery;

	game->player.rotation_angle += game->player.turndirection * \
		game->player.turn_speed * deltaTime;
	game->player.rotation_angle = normalizeangle(game->player.rotation_angle);
	if (!game->player.sidedirection)
	{
		movestep = game->player.walkdirection * \
			game->player.walk_speed * deltaTime;
		newplayerx = game->player.p_x + \
			cos(game->player.rotation_angle) * movestep;
		newplayery = game->player.p_y + \
			sin(game->player.rotation_angle) * movestep;
	}
	if (game->player.sidedirection)
	{
		movestep = game->player.sidedirection * \
			game->player.walk_speed * deltaTime;
		newplayerx = game->player.p_x - \
			sin(game->player.rotation_angle) * movestep;
		newplayery = game->player.p_y + \
			cos(game->player.rotation_angle) * movestep;
	}
	check_movement(game, newplayerx, newplayery);
}

void	renderplayer(t_game *game)
{
	float	movestep;

	movestep = 0.0;
	moveplayer(game, movestep, 0.3);
}
