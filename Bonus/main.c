/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:22:37 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/04 17:10:40 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

double	degtorad(double degree)
{
	return (degree * (M_PI / 180.0));
}

void	ft_mouse(double x, double y, void *param)
{
	t_game			*game;
	static int		i;

	(void)y;
	game = (t_game *)param;
	if (i == 0)
		x = WIDTH / 2;
	if (i != x)
		game->player.rotation_angle = degtorad((x - i) / 20)
			+ game->player.rotation_angle;
	i = x;
}

void	handlemouseclick(enum mouse_key button, enum action act,
	enum modifier_key mod, void *param)
{
	t_game	*game;

	(void)mod;
	game = (t_game *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS && !game->gun_state)
	{
		game->gun_state = 1;
		system("afplay ./Bonus/pictures/rpg7e.mp3&");
	}
}

int	main(int argc, char *argv[])
{
	t_game		*game;
	size_t		i;

	game = my_malloc(sizeof(t_game), 1, 1);
	if (argc != 2)
		error_out("Error: Wrong number of arguments\n", 0, NULL);
	else
	{
		i = ft_strlen(argv[1]) - 1;
		if (argv[1][i] == 'b' && argv[1][i - 1] == 'u' && argv[1][i - 2] == 'c'
				&& argv[1][i - 3] == '.')
		{
			setting_data_1(&game);
			parce_the_file(argv, &game);
		}
		else
			error_out("Error: Wrong File Format. Format is '*.cub'\n", 0, NULL);
	}
	create_mlx(game);
	data_setup(game);
	mlx_hooks(game);
	mlx_loop(game->mlx->mlx);
	mlx_terminate(game->mlx->mlx);
	my_malloc(0, 0, 0);
	return (0);
}
