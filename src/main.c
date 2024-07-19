/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:07 by alimpens          #+#    #+#             */
/*   Updated: 2024/07/19 15:04:39 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_callback(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_terminate(game->mlx);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_game			game;
	t_validation	validation;

	check_file(argc, argv);
	load_map_dimensions_from_file(&game, argv[1]);
	validate_file(&game, argv[1], &validation);
	allocate_map(&game);
	fill_2d_map_from_file(&game, argv[1]);
	print_map_grid_2d(&game);
	check_map_surrounded(&game);
	init_game(&game);
	game.mlx = mlx_init(WIDTH, HEIGHT, "Welcome to DOOOOOOOOM!!!!!!", false);
	game.image = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.image || (mlx_image_to_window(game.mlx, game.image, 0, 0) < 0))
		ft_error(ERR_IMG, NULL);
	open_and_get_textures(argv[1], &game);
	load_all_textures_set_colors(&game, &validation);
	mlx_key_hook(game.mlx, my_keyhook, &game);
	mlx_close_hook(game.mlx, close_callback, &game);
	mlx_loop_hook(game.mlx, draw_all_and_clear, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_map_grid_2d(&game);
	return (EXIT_SUCCESS);
}
