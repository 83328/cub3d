/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:55 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/23 17:31:03 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_rotation_keys(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->key_left_pressed = true;
	if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->key_right_pressed = true;
}

void	handle_movement_keys(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->key_w_pressed = true;
	if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->key_s_pressed = true;
	if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->key_a_pressed = true;
	if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		game->key_d_pressed = true;
}

// this might not be the best way,
// maybe we should use the MLX_CLOSE_WINDOW event
// this causes a possible memory leak
void	handle_escape_key(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(0);
}

void reset_keys(t_game *game)
{
	game->key_a_pressed = false;
	game->key_s_pressed = false;
	game->key_d_pressed = false;
	game->key_w_pressed = false;
	game->key_left_pressed = false;
	game->key_right_pressed = false;
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = (t_game *)param;
	handle_rotation_keys(keydata, game);
	handle_movement_keys(keydata, game);
	handle_escape_key(keydata);
}
