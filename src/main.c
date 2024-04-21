/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:07 by alimpens          #+#    #+#             */
/*   Updated: 2024/04/21 18:15:55 by ohoro            ###   ########.fr       */
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
	game->key_a_pressed = false;
	game->key_s_pressed = false;
	game->key_d_pressed = false;
	game->key_w_pressed = false;
	game->key_left_pressed = false;
	game->key_right_pressed = false;
}

void	init_test_line(t_line *line)
{
	line->x0 = 100;
	line->y0 = 100;
	line->x1 = 200;
	line->y1 = 200;
}


int32_t main(void)
{
	t_game game;
	init_game(&game);

	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Welcome to DOOOOOOOOOOOOOM!!!!!!!!!!!!!!!", false);
	game.mlx = mlx;
	
	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		printf("Failed to create image\n");
	// draw three pixels
	game.image = img;
	//bresenham(line, player.image);
	
	mlx_key_hook(mlx, my_keyhook, &game);
	mlx_loop_hook(mlx, redraw_player, &game);
	mlx_loop(mlx);
	
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
