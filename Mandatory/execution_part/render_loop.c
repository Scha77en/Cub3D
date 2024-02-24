/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:08:05 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/03 10:12:36 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render(t_game *game)
{
	castallrays(game);
	renderplayer(game);
}

void	loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	render(game);
}
