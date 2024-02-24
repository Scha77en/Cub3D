/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:08:05 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/09 07:26:00 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	disable_images(t_game *game)
{
	game->data->gun_frames[0]->enabled = true;
	game->data->gun_frames[1]->enabled = false;
	game->data->gun_frames[2]->enabled = false;
	game->data->gun_frames[3]->enabled = false;
	game->data->gun_frames[4]->enabled = false;
	game->data->gun_frames[5]->enabled = false;
	game->data->gun_frames[6]->enabled = false;
	game->data->gun_frames[7]->enabled = false;
	game->data->gun_frames[8]->enabled = false;
	game->data->gun_frames[9]->enabled = false;
	game->data->gun_frames[10]->enabled = false;
	game->data->gun_frames[11]->enabled = false;
	game->data->gun_frames[12]->enabled = false;
	game->data->gun_frames[13]->enabled = false;
	game->data->gun_frames[14]->enabled = false;
	game->data->gun_frames[15]->enabled = false;
	game->data->gun_frames[16]->enabled = false;
	game->data->gun_frames[17]->enabled = false;
	game->data->gun_frames[18]->enabled = false;
	game->data->gun_frames[19]->enabled = false;
	game->data->gun_frames[20]->enabled = false;
	game->data->gun_frames[21]->enabled = false;
	game->data->gun_frames[22]->enabled = false;
	game->data->gun_frames[24]->enabled = false;
	disable_images2(game);
}

void	disable_images2(t_game *game)
{
	game->data->gun_frames[23]->enabled = false;
	game->data->gun_frames[25]->enabled = false;
	game->data->gun_frames[26]->enabled = false;
	game->data->gun_frames[27]->enabled = false;
	game->data->gun_frames[28]->enabled = false;
	game->data->gun_frames[29]->enabled = false;
	game->data->gun_frames[30]->enabled = false;
	game->data->gun_frames[31]->enabled = false;
	game->data->gun_frames[32]->enabled = false;
	game->data->gun_frames[33]->enabled = false;
	game->data->gun_frames[34]->enabled = false;
	game->data->gun_frames[35]->enabled = false;
	game->data->gun_frames[36]->enabled = false;
	game->data->gun_frames[37]->enabled = false;
	game->data->gun_frames[38]->enabled = false;
	game->data->gun_frames[39]->enabled = false;
	game->data->gun_frames[40]->enabled = false;
	game->data->gun_frames[41]->enabled = false;
	game->data->gun_frames[42]->enabled = false;
	game->data->gun_frames[43]->enabled = false;
	game->data->gun_frames[44]->enabled = false;
}

void	render(t_game *game)
{
	castallrays(game);
	minimap_setup(game);
	renderplayer(game);
	if (game->gun_state == true)
		animate_gun(game);
}

void	animate_gun(t_game *game)
{
	static int	delay;

	game->data->gun_frames[game->data->frame]->enabled = false;
	if (delay % 2 == 0)
		game->data->frame++;
	if (game->data->frame >= 45)
	{
		game->gun_state = false;
		game->data->frame = 0;
	}
	delay++;
	game->data->gun_frames[game->data->frame]->enabled = true;
}/**/

void	loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	render(game);
}
