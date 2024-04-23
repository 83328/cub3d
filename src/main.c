/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:07 by alimpens          #+#    #+#             */
/*   Updated: 2024/04/23 18:33:47 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_game(t_game *game)
{
	game->mlx = NULL;
	game->image = NULL;
	game->player_x = 100;
	game->player_y = 100;
	game->player_width = 1;
	game->player_height = 1;
	game->player_rotation_angle = 0;
	game->key_a_pressed = 0;
	game->key_s_pressed = 0;
	game->key_d_pressed = 0;
	game->key_w_pressed = 0;
	game->key_left_pressed = 0;
	game->key_right_pressed = 0;
}

void	init_test_line(t_line *line)
{
	line->x0 = 100;
	line->y0 = 100;
	line->x1 = 200;
	line->y1 = 200;
}

int	validate_input_and_load_map(int argc, char **argv, t_game *game)
{
	if (argc != 2)
	{
		printf("Usage: ./cub3d ./maps/mapfile.cub\n");
		return (0);
	}
	if (!load_map(game, argv[1]))
	{
		printf("Failed to load map\n");
		return (0);
	}
	if (!check_map_validity(game->map))
	{
		printf("Invalid map\n");
		return (0);
	}
	return (1);
}

int32_t	main(int argc, char **argv)
{
	t_game game;

	if (!validate_input_and_load_map(argc, argv, &game))
	{
		return (EXIT_FAILURE);
	}
	init_game(&game);
	game.mlx = mlx_init(WIDTH, HEIGHT, "Welcome to DOOOOOOOOOOOOOM!!!!!!!!!!!!!!!", false);
	game.image = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.image || (mlx_image_to_window(game.mlx, game.image, 0, 0) < 0))
		printf("Failed to create image\n");
	mlx_key_hook(game.mlx, my_keyhook, &game);
	mlx_loop_hook(game.mlx, redraw_player, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
