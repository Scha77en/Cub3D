/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:11:37 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/04 17:45:29 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->player.walkdirection = 0;
	game->player.sidedirection = 0;
	game->player.turndirection = 0;
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_W))
		game->player.walkdirection = 1;
	else if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_S))
		game->player.walkdirection = -1;
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_A))
		game->player.sidedirection = -1;
	else if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_D))
		game->player.sidedirection = 1;
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_LEFT))
		game->player.turndirection = -1;
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_RIGHT))
		game->player.turndirection = 1;
}

void	cross(void *param)
{
	(void)param;
	exit(0);
}

void	mlx_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx->mlx, &ft_hook, game);
	mlx_close_hook(game->mlx->mlx, &cross, game);
	mlx_loop_hook(game->mlx->mlx, &loop, game);
}

void	create_mlx(t_game *game)
{
	game->mlx->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!(game->mlx->mlx))
		error_out("mlx_init", 1, game->data);
	game->mlx->img = mlx_new_image(game->mlx->mlx, WIDTH, HEIGHT);
	if (!(game->mlx->img))
	{
		mlx_close_window(game->mlx->mlx);
		error_out("mlx_new_image", 1, game->data);
	}
	if (mlx_image_to_window(game->mlx->mlx, game->mlx->img, 0, 0) == -1)
	{
		mlx_close_window(game->mlx->mlx);
		error_out("mlx_image_to_window", 1, game->data);
	}
}
