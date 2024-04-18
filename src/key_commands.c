/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:55 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/18 16:55:02 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_rotation(mlx_key_data_t keydata, t_player *player)
{
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->rotation_angle -= 0.1;
		printf("left turn and Rotation Angle: %f\n", player->rotation_angle);
	}
	if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->rotation_angle += 0.1;
		printf("right turn and Rotation Angle: %f\n", player->rotation_angle);
	}
}

void	handle_movement(mlx_key_data_t keydata, t_player *player)
{
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->x += 1;
		printf("x: %f, y: %f\n", player->x, player->y);
	}
	if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->x -= 1;
		printf("x: %f, y: %f\n", player->x, player->y);
	}
	if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->y += 1;
		printf("x: %f, y: %f\n", player->x, player->y);
	}
	if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		player->y -= 1;
		printf("x: %f, y: %f\n", player->x, player->y);
	}
}

// this might not be the best way,
// maybe we should use the MLX_CLOSE_WINDOW event
void	handle_escape(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(0);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_player	*player;

	player = (t_player *)param;
	handle_rotation(keydata, player);
	handle_movement(keydata, player);
	handle_escape(keydata);
}
