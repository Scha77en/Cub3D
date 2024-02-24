/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 02:30:27 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/03 08:49:24 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	distance_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	distance(t_game *game, t_ray *ray)
{
	ray->distance_hor = 0;
	if (ray->found_hit_horizontal)
		ray->distance_hor = distance_points(game->player.p_x,
				game->player.p_y, ray->wall_hit_hor_x, ray->wall_hit_hor_y);
	else
		ray->distance_hor = HIGH_VALUE;
	ray->distance_ver = 0;
	if (ray->found_hit_vertical)
		ray->distance_ver = distance_points(game->player.p_x,
				game->player.p_y, ray->wall_hit_ver_x, ray->wall_hit_ver_y);
	else
		ray->distance_ver = HIGH_VALUE;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	rendering_distance(game, ray);
}

void	rendering_distance(t_game *game, t_ray *ray)
{
	if (ray->distance_hor > ray->distance_ver)
	{
		ray->was_hit_vertical = TRUE;
		ray->wall_hit_x = ray->wall_hit_ver_x;
		ray->wall_hit_y = ray->wall_hit_ver_y;
		ray->distance = ray->distance_ver;
		if (ray->is_ray_facing_right)
			game->ray.text = game->data->east_tex;
		else
			game->ray.text = game->data->west_tex;
	}
	else
	{
		ray->was_hit_vertical = FALSE;
		ray->wall_hit_x = ray->wall_hit_hor_x;
		ray->wall_hit_y = ray->wall_hit_hor_y;
		ray->distance = ray->distance_hor;
		if (ray->is_ray_facing_up)
			game->ray.text = game->data->north_tex;
		else
			game->ray.text = game->data->south_tex;
	}
}
