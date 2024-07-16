/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:07 by alimpens          #+#    #+#             */
/*   Updated: 2024/07/16 15:01:03 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	init_direction(char direction)
{
	if (direction == 'W')
		return (3.10);
	else if (direction == 'S')
		return (1.50);
	else if (direction == 'N')
		return (4.70);
	else if (direction == 'E')
		return (6.20);
	else
		return (-1);
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->image = NULL;
	game->player_width = 1;
	game->player_height = 1;
	game->player_rotation_angle = init_direction(game->start_direction);
}

void	init_test_line(t_line *line)
{
	line->x0 = 100;
	line->y0 = 100;
	line->x1 = 200;
	line->y1 = 200;
}

int	main(int argc, char **argv)
{
	t_game			game;
	t_validation	validation;

	check_file(argc, argv);
	validate_file(argv[1], &validation);
	load_map_dimensions_from_file(&game, argv[1]);
	printf("Map Dimensions: %d x %d\n", game.map_rows, game.map_cols);
	printf("Map start: %d\n", game.map_start);
	printf("Map end: %d\n", game.map_end);
	printf("Map height: %d\n", game.map_rows);
	allocate_map(&game);
	fill_2d_map_from_file(&game, argv[1]);
	print_map_grid_2d(&game);
	check_map_surrounded(&game);
	init_game(&game);
	game.mlx = mlx_init(WIDTH, HEIGHT, "Welcome to DOOOOOOOOM!!!!!!", false);
	game.image = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (!game.image || (mlx_image_to_window(game.mlx, game.image, 0, 0) < 0))
		ft_error(ERR_IMG, NULL);
	load_test_texture_north(&game);
	load_test_texture_east(&game);
	load_test_texture_south(&game);
	load_test_texture_west(&game);
	mlx_key_hook(game.mlx, my_keyhook, &game);
	mlx_loop_hook(game.mlx, draw_all_and_clear, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_map_grid_2d(&game);
	return (EXIT_SUCCESS);
}
