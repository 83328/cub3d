/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:07 by alimpens          #+#    #+#             */
/*   Updated: 2024/04/18 17:34:30 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player	*player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->width = 10;
	player->height = 10;
	player->rotation_angle = 0;
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
	t_player player;
	init_player(&player);

	t_line line;
	init_test_line(&line);

	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Welcome to DOOOOOOOOOOOOOM!!!!!!!!!!!!!!!", false);

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		printf("Failed to create image\n");
	// draw three pixels
	bresenham(line, img);
	
	mlx_key_hook(mlx, &my_keyhook, &player);
	mlx_loop(mlx);
	


	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
