/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:25:34 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/04 17:12:37 by aouhbi           ###   ########.fr       */
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
	sprite_setup(game);
}

void	sprite_setup(t_game *game)
{
	mlx_texture_t	*texture;
	char			**gunframe;
	int				i;

	gunframe = load_frames();
	game->data->frame = 0;
	game->gun_state = 0;
	i = 0;
	while (i < 45)
	{
		texture = mlx_load_png(gunframe[i]);
		if (!texture)
			error_out("mlx_load_png", 1, game->data);
		game->data->gun_frames[i]
			= mlx_texture_to_image(game->mlx->mlx, texture);
		if (!game->data->gun_frames[i]
			|| mlx_image_to_window(game->mlx->mlx, game->data->gun_frames[i],
				(int32_t){0}, (int32_t){0}) == -1)
			error_out("mlx_texture_to_image", 1, game->data);
		mlx_delete_texture(texture);
		i++;
	}
	disable_images(game);
}

void	load_frames1(char *gunframe[45])
{
	gunframe[21] = "Bonus/pictures/animation/21.png";
	gunframe[22] = "Bonus/pictures/animation/22.png";
	gunframe[23] = "Bonus/pictures/animation/23.png";
	gunframe[24] = "Bonus/pictures/animation/24.png";
	gunframe[25] = "Bonus/pictures/animation/25.png";
	gunframe[26] = "Bonus/pictures/animation/26.png";
	gunframe[27] = "Bonus/pictures/animation/27.png";
	gunframe[28] = "Bonus/pictures/animation/28.png";
	gunframe[29] = "Bonus/pictures/animation/29.png";
	gunframe[30] = "Bonus/pictures/animation/30.png";
	gunframe[31] = "Bonus/pictures/animation/31.png";
	gunframe[32] = "Bonus/pictures/animation/32.png";
	gunframe[33] = "Bonus/pictures/animation/33.png";
	gunframe[34] = "Bonus/pictures/animation/34.png";
	gunframe[35] = "Bonus/pictures/animation/35.png";
	gunframe[36] = "Bonus/pictures/animation/36.png";
	gunframe[37] = "Bonus/pictures/animation/37.png";
	gunframe[38] = "Bonus/pictures/animation/38.png";
	gunframe[39] = "Bonus/pictures/animation/39.png";
	gunframe[40] = "Bonus/pictures/animation/40.png";
	gunframe[41] = "Bonus/pictures/animation/41.png";
	gunframe[42] = "Bonus/pictures/animation/42.png";
	gunframe[43] = "Bonus/pictures/animation/43.png";
	gunframe[44] = "Bonus/pictures/animation/44.png";
}

char	**load_frames(void)
{
	static char		*gunframe[45];

	gunframe[0] = "Bonus/pictures/animation/0.png";
	gunframe[1] = "Bonus/pictures/animation/1.png";
	gunframe[2] = "Bonus/pictures/animation/2.png";
	gunframe[3] = "Bonus/pictures/animation/3.png";
	gunframe[4] = "Bonus/pictures/animation/4.png";
	gunframe[5] = "Bonus/pictures/animation/5.png";
	gunframe[6] = "Bonus/pictures/animation/6.png";
	gunframe[7] = "Bonus/pictures/animation/7.png";
	gunframe[8] = "Bonus/pictures/animation/8.png";
	gunframe[9] = "Bonus/pictures/animation/9.png";
	gunframe[10] = "Bonus/pictures/animation/10.png";
	gunframe[11] = "Bonus/pictures/animation/11.png";
	gunframe[12] = "Bonus/pictures/animation/12.png";
	gunframe[13] = "Bonus/pictures/animation/13.png";
	gunframe[14] = "Bonus/pictures/animation/14.png";
	gunframe[15] = "Bonus/pictures/animation/15.png";
	gunframe[16] = "Bonus/pictures/animation/16.png";
	gunframe[17] = "Bonus/pictures/animation/17.png";
	gunframe[18] = "Bonus/pictures/animation/18.png";
	gunframe[19] = "Bonus/pictures/animation/19.png";
	gunframe[20] = "Bonus/pictures/animation/20.png";
	load_frames1(gunframe);
	return (gunframe);
}
