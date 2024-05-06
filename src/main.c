/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:07 by alimpens          #+#    #+#             */
/*   Updated: 2024/05/06 11:35:52 by alimpens         ###   ########.fr       */
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
	game->player_rotation_angle = M_PI_2;
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
/* 	if (!check_map_validity(game->map))
	{
		printf("Invalid map\n");
		return (0);
	} */
	return (1);
}

void load_map_from_file(t_game *game, char *argv)
{
//	int fd = open("./maps/test_map.cub", O_RDONLY);
	int fd = open(argv, O_RDONLY);
	printf("Loading map from file...\n");
	if (fd < 0)
	{
		printf("Failed to open file\n");
		return;
	}
	int i = 0;
	while (i < MAP_NUM_ROWS)
	{
		char *line = get_next_line(fd);
		if (line == NULL)
		{
			printf("Failed to read line\n");
			close(fd);
			return;
		}
		int j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (line[j] == '0')
				game->map_grid[i][j] = 0;
			else if (line[j] == '1')
				game->map_grid[i][j] = 1;
			else
			{
				printf("Invalid character in map. Only '0' and '1' are allowed.\n");
				free(line);
				close(fd);
				return;
			}
			j++;
		}
		free(line);
		i++;
	}
	close(fd);
}

void	print_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			printf("%d", game->map_grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	init_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			game->map_grid[i][j] = 0;
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_game game;
	//t_map map;
	
	/* int test_map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	}; */

	// copy map to game.map_grid
/* 	for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (int j = 0; j < MAP_NUM_COLS; j++)
		{
			game.map_grid[i][j] = test_map[i][j];
		}
	}; */
	init_map(&game);

	//close(fd);
	load_map_from_file(&game, argv[1]);
	print_map(&game);
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
	mlx_loop_hook(game.mlx, draw_all_and_clear, &game);
	//mlx_loop_hook(game.mlx, draw_map, &game);
	//mlx_loop_hook(game.mlx, redraw_player, &game);
	//mlx_loop_hook(game.mlx, clear_image, &game);
	//mlx_loop_hook(game.mlx, cast_all_rays, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
