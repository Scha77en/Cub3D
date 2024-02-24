/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:10:14 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/04 16:23:16 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	intersaction(int stripId, t_game *game, t_ray *ray)
{
	int		k;

	k = 0;
	intersactionhor(stripId, game, ray);
	intersactionver(stripId, game, ray);
	distance(game, ray);
	render3d_projection(game, stripId, ray, k);
}

void	castray(int stripId, t_game *game, t_ray *ray)
{
	game->ray.ray_angle = normalizeangle(game->ray.ray_angle);
	ray->is_ray_facing_down = FALSE;
	ray->is_ray_facing_up = FALSE;
	ray->is_ray_facing_right = FALSE;
	ray->is_ray_facing_left = FALSE;
	if (ray->ray_angle > 0 && ray->ray_angle <= degtorad(180.0))
		ray->is_ray_facing_down = TRUE;
	if (!ray->is_ray_facing_down)
		ray->is_ray_facing_up = TRUE;
	if (ray->ray_angle < degtorad(90.0) || ray->ray_angle > degtorad(270.0))
		ray->is_ray_facing_right = TRUE;
	if (!ray->is_ray_facing_right)
		ray->is_ray_facing_left = TRUE;
	intersaction(stripId, game, ray);
}

float	normalizeangle(float angle)
{
	angle = remainder(angle, degtorad(360.0));
	if (angle < 0)
		angle += degtorad(360.0);
	return (angle);
}

void	castallrays(t_game *game)
{
	t_ray	ray;
	int		i;

	i = 0;
	ray.ray_angle = game->player.rotation_angle - (degtorad(FOV_ANGLE) / 2);
	ray.increment_angle = degtorad(FOV_ANGLE) / WIDTH;
	ray.ray_angle = normalizeangle(ray.ray_angle);
	while (i < WIDTH)
	{
		castray(i, game, &ray);
		ray.ray_angle += ray.increment_angle;
		ray.ray_angle = normalizeangle(ray.ray_angle);
		i++;
	}
}
