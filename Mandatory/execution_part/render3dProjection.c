/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3dProjection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:32:29 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/04 18:35:47 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_get_color(int i, int x, int y, t_game *game)
{
	int		r;
	int		g;
	int		b;

	(void)i;
	r = game->ray.text->pixels[y * (game->ray.text->width * 4) + (x * 4)];
	g = game->ray.text->pixels[y * (game->ray.text->width * 4) + (x * 4) + 1];
	b = game->ray.text->pixels[y * (game->ray.text->width * 4) + (x * 4) + 2];
	return (ft_pixel(r, g, b, 255));
}

void	render3d_projection(t_game *game, int stripId, t_ray *ray, int k)
{
	ray->distance *= cos(ray->ray_angle - game->player.rotation_angle);
	game->ray.distance_projection_plane = (WIDTH / 2)
		/ tan(degtorad(FOV_ANGLE) / 2);
	ray->real_wall_height = (game->ray.distance_projection_plane
			/ ray->distance) * TILE_SIZE;
	ray->correct_wall_height = ray->real_wall_height;
	if (ray->real_wall_height > HEIGHT)
		ray->correct_wall_height = HEIGHT;
	game->element->topprojection = (HEIGHT / 2)
		- (ray->correct_wall_height / 2);
	game->element->bottomprojection = ray->correct_wall_height
		+ game->element->topprojection;
	k = 0;
	while (game->element->topprojection >= k)
	{
		mlx_put_pixel(game->mlx->img, stripId, k,
			ft_pixel(game->data->ceiling_data->r_c,
				game->data->ceiling_data->b_c,
				game->data->ceiling_data->g_c, 255));
		k++;
	}
	wall_rendring(game, stripId, ray);
	ceiling_rendering(game, stripId);
}

void	ceiling_rendering(t_game *game, int stripId)
{
	while (game->element->bottomprojection < HEIGHT)
	{
		mlx_put_pixel(game->mlx->img, stripId, game->element->bottomprojection,
			ft_pixel(game->data->floor_data->r_f,
				game->data->floor_data->g_f,
				game->data->floor_data->b_f, 255));
		game->element->bottomprojection++;
	}
}

void	wall_rendring(t_game *game, int stripId, t_ray *ray)
{
	float	offset_x;
	float	offset_y;
	int		color;

	if (ray->was_hit_vertical)
		offset_x = fmodf(ray->wall_hit_y, TILE_SIZE)
			* ((float)game->ray.text->width / TILE_SIZE);
	else
		offset_x = fmodf(ray->wall_hit_x, TILE_SIZE)
			* ((float)game->ray.text->width / TILE_SIZE);
	while (game->element->topprojection < game->element->bottomprojection)
	{
		offset_y = (game->element->topprojection
				+ (ray->real_wall_height / 2) - (HEIGHT / 2))
			* ((float)game->ray.text->height / ray->real_wall_height);
		if (offset_y >= game->ray.text->height)
			offset_y = game->ray.text->height - 1;
		color = ft_get_color(game->element->topprojection,
				offset_x, offset_y, game);
		mlx_put_pixel(game->mlx->img, stripId,
			game->element->topprojection, color);
		game->element->topprojection++;
	}
}
