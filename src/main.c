/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:32:07 by alimpens          #+#    #+#             */
/*   Updated: 2024/04/18 14:27:38 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>

#define WIDTH 512
#define HEIGHT 512
#define M_PI_2 1.57079632679489661923

typedef struct s_player
{
	float x;
    float y;
    float width;
    float height;
    float rotationAngle; 
} t_player;

void initPlayer(t_player* player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->width = 10;
	player->height = 10;
	player->rotationAngle = 0;
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_player* player = (t_player*)param;

	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->rotationAngle -= 0.1;
		printf("left turn and Rotation Angle: %f\n", player->rotationAngle);
	}
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->rotationAngle += 0.1;

		printf("right turn and Rotation Angle: %f\n", player->rotationAngle);
	}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->x += 1;
		printf("x: %f, y: %f\n", player->x, player->y);
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->x -= 1;
		printf("x: %f, y: %f\n", player->x, player->y);
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->y += 1;
		printf("x: %f, y: %f\n", player->x, player->y);
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->y -= 1;
		printf("x: %f, y: %f\n", player->x, player->y);
	}
}

// bresenham's line algorithm
void drawLine(mlx_image_t* img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1)
	{
		mlx_put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}



int32_t main(void)
{
	t_player player;
	initPlayer(&player);


	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Welcome to DOOOOOOOOOOOOOM!!!!!!!!!!!!!!!", false);

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	drawLine(img, 25, 25, 100, 100, 0xFF0000);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		printf("Failed to create image\n");
	// draw a simple red line in the middle of the screen
	
	mlx_key_hook(mlx, &my_keyhook, &player);
	mlx_loop(mlx);
	


	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
