/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:07 by alimpens          #+#    #+#             */
/*   Updated: 2024/04/18 16:43:26 by ohoro            ###   ########.fr       */
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


int32_t main(void)
{
	t_player player;
	init_player(&player);


	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Welcome to DOOOOOOOOOOOOOM!!!!!!!!!!!!!!!", false);

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		printf("Failed to create image\n");
	// draw three pixels
	put_pixel(242, 242, img);
	put_pixel(243, 243, img);	
	put_pixel(244, 244, img);
	
	mlx_key_hook(mlx, &my_keyhook, &player);
	mlx_loop(mlx);
	


	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
