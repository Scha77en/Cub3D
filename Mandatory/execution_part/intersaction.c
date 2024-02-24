/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersaction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:30:40 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/03 07:40:04 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	increment_xy_ver(t_game *game, t_ray *ray)
{
	ray->found_hit_vertical = FALSE;
	ray->wall_hit_ver_x = 0;
	ray->wall_hit_ver_y = 0;
	while (ray->next_vert_touch_x >= 0 && \
		ray->next_vert_touch_x <= game->data->map_width * TILE_SIZE \
		&& ray->next_vert_touch_y >= 0 \
		&& ray->next_vert_touch_y <= game->data->map_height * TILE_SIZE)
	{
		ray->tmp_her_x = ray->next_vert_touch_x;
		if (ray->is_ray_facing_left)
			ray->tmp_her_x--;
		if (maphaswallat_rays(game, ray->tmp_her_x, ray->next_vert_touch_y))
		{
			ray->found_hit_vertical = TRUE;
			ray->wall_hit_ver_x = ray->next_vert_touch_x;
			ray->wall_hit_ver_y = ray->next_vert_touch_y;
			break ;
		}
		else
		{
			ray->next_vert_touch_x += ray->x_step;
			ray->next_vert_touch_y += ray->y_step;
		}
	}
}

void	intersactionver(int stripId, t_game *game, t_ray *ray)
{
	double	xintercept;
	double	yintercept;

	(void)stripId;
	xintercept = floor(game->player.p_x \
	/ (double)TILE_SIZE) * (double)TILE_SIZE;
	if (ray->is_ray_facing_right)
		xintercept += (double)TILE_SIZE;
	yintercept = game->player.p_y \
		+ ((xintercept - game->player.p_x) * tan(ray->ray_angle));
	ray->x_step = (double)TILE_SIZE;
	if (ray->is_ray_facing_left)
		ray->x_step *= -1;
	ray->y_step = (double)TILE_SIZE * tan(ray->ray_angle);
	if ((ray->is_ray_facing_up && ray->y_step > 0) || \
		(ray->is_ray_facing_down && ray->y_step < 0))
		ray->y_step *= -1;
	ray->next_vert_touch_x = xintercept;
	ray->next_vert_touch_y = yintercept;
	increment_xy_ver(game, ray);
}

void	increment_xy_hor(t_game *game, t_ray *ray)
{
	ray->found_hit_horizontal = FALSE;
	ray->wall_hit_hor_x = 0;
	ray->wall_hit_hor_y = 0;
	while (ray->next_horz_touch_x >= 0 && \
			ray->next_horz_touch_x <= game->data->map_width * TILE_SIZE \
			&& ray->next_horz_touch_y >= 0 \
			&& ray->next_horz_touch_y <= game->data->map_height * TILE_SIZE)
	{
		ray->tmp_her_y = ray->next_horz_touch_y;
		if (ray->is_ray_facing_up)
			ray->tmp_her_y--;
		if (maphaswallat_rays(game, ray->next_horz_touch_x, ray->tmp_her_y))
		{
			ray->found_hit_horizontal = TRUE;
			ray->wall_hit_hor_x = ray->next_horz_touch_x;
			ray->wall_hit_hor_y = ray->next_horz_touch_y;
			break ;
		}
		else
		{
			ray->next_horz_touch_x += ray->x_step;
			ray->next_horz_touch_y += ray->y_step;
		}
	}
}

void	intersactionhor(int stripId, t_game *game, t_ray *ray)
{
	double	xintercept;
	double	yintercept;

	(void)stripId;
	yintercept = floor(game->player.p_y \
		/ (double)TILE_SIZE) * (double)TILE_SIZE;
	if (ray->is_ray_facing_down)
		yintercept += (double)TILE_SIZE;
	xintercept = game->player.p_x \
		+ ((yintercept - game->player.p_y) / tan(ray->ray_angle));
	ray->y_step = (double)TILE_SIZE;
	if (ray->is_ray_facing_up)
		ray->y_step *= -1;
	ray->x_step = (double)TILE_SIZE / tan(ray->ray_angle);
	if ((ray->is_ray_facing_left && ray->x_step > 0) || \
		(ray->is_ray_facing_right && ray->x_step < 0))
		ray->x_step *= -1;
	ray->next_horz_touch_x = xintercept;
	ray->next_horz_touch_y = yintercept;
	increment_xy_hor(game, ray);
}
