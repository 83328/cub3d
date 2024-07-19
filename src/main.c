/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:07 by alimpens          #+#    #+#             */
/*   Updated: 2024/07/19 15:00:46 by ohoro            ###   ########.fr       */
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
	game->floor_color = 0;
	game->ceiling_color = 0;
}

void	init_test_line(t_line *line)
{
	line->x0 = 100;
	line->y0 = 100;
	line->x1 = 200;
	line->y1 = 200;
}

void	close_callback(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_terminate(game->mlx);
	exit(0);
}

void	open_and_get_textures(char *filepath, t_game *game)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		ft_error(ERR_OPEN, NULL);
	}
	get_textures(fd, game);
	close(fd);
}
void load_all_textures_set_colors(t_game *game, t_validation *v)
{
	load_test_texture_north(game);
	load_test_texture_east(game);
	load_test_texture_south(game);
	load_test_texture_west(game);
	game->ceiling_color = get_rgba(v->c_red, v->c_green, 
			v->c_blue, 255);
	game->floor_color = get_rgba(v->f_red, v->f_green, 
			v->f_blue, 255);
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
