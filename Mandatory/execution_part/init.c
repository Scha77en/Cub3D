/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:25:34 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/04 16:54:50 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	data_setup(t_game *game)
{
	game->player.walk_speed = 10;
	game->player.turn_speed = degtorad(5.0);
	game->player.turndirection = 0;
	game->player.walkdirection = 0;
	game->player.sidedirection = 0;
	game->player.new_x = 0;
	game->player.new_y = 0;
	game->player.movestep = 0;
	game->player.width = 0;
	game->player.height = 0;
	game->player.dx = 0;
	game->player.dy = 0;
	if (game->player.position_player == 'N')
		game->player.rotation_angle = degtorad(270.0);
	else if (game->player.position_player == 'S')
		game->player.rotation_angle = degtorad(90.0);
	else if (game->player.position_player == 'E')
		game->player.rotation_angle = degtorad(360.0);
	else if (game->player.position_player == 'W')
		game->player.rotation_angle = degtorad(180.0);
	game->element = my_malloc(sizeof(t_element), 1, 1);
	data_setup1(game);
}

void	data_setup1(t_game *game)
{
	game->ray.is_ray_facing_down = FALSE;
	game->ray.is_ray_facing_up = FALSE;
	game->ray.is_ray_facing_left = FALSE;
	game->ray.is_ray_facing_right = FALSE;
	game->ray.wall_hit_x = 0;
	game->ray.wall_hit_y = 0;
	game->ray.distance = 0;
	game->ray.wall_hit_hor_x = 0;
	game->ray.wall_hit_hor_y = 0;
	game->ray.wall_hit_ver_x = 0;
	game->ray.wall_hit_ver_y = 0;
	game->data->frame = 0;
	game->data->mouse_clicked = false;
	game->ray.found_hit_horizontal = FALSE;
	game->ray.found_hit_vertical = FALSE;
	game->gun_state = 0;
}
