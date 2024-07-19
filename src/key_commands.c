/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:55 by ohoro             #+#    #+#             */
/*   Updated: 2024/07/19 14:17:06 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_position(t_game *game, float dx, float dy)
{
	if (game->player_y + dy > TILE_SIZE && game->player_y + 
		dy < ((game->map_rows - 1) * TILE_SIZE))
	{
		game->player_y += dy;
	}
	if (game->player_x + dx > TILE_SIZE && game->player_x + 
		dx < ((game->map_cols - 1) * TILE_SIZE))
	{
		game->player_x += dx;
	}
}

void	update_movement(t_game *game, float move_speed, mlx_key_data_t keydata)
{
	(void)keydata;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player_rotation_angle -= 0.1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player_rotation_angle += 0.1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_forward(game, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_backward(game, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_left(game, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_right(game, move_speed);
}

void	handle_movement_and_rotation_keys(mlx_key_data_t keydata, t_game *game)
{
	float	move_speed;

	move_speed = 2.0f;
	update_movement(game, move_speed, keydata);
}

void	handle_escape_key(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
		exit(0);
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_movement_and_rotation_keys(keydata, game);
	handle_escape_key(keydata, game);
}
