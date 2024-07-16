/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:55 by ohoro             #+#    #+#             */
/*   Updated: 2024/07/16 14:21:53 by alimpens         ###   ########.fr       */
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

// this might not be the best way,
// maybe we should use the MLX_CLOSE_WINDOW event
// this causes a possible memory leak
void	handle_escape_key(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		free_game(game);
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
/*
#if 0
OLD CODE: kept for learning reasons

void update_movement(t_game *game, float move_speed, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || 
		keydata.action == MLX_REPEAT))
		move_forward(game, move_speed);
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || 
		keydata.action == MLX_REPEAT))
		move_backward(game, move_speed);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || 
		keydata.action == MLX_REPEAT))
		move_left(game, move_speed);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || 
		keydata.action == MLX_REPEAT))
		move_right(game, move_speed);
}

void handle_movement_and_rotation_keys(mlx_key_data_t keydata, t_game *game)
{
	float move_speed;
	move_speed = 2.0f;

	if (keydata.key == MLX_KEY_W) {
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
			game->key_w_pressed = 1;
		}
		if (keydata.action == MLX_RELEASE) {
			game->key_w_pressed = 0;
		}
	}
	if (keydata.key == MLX_KEY_S) {
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
			game->key_s_pressed = 1;
		}
		if (keydata.action == MLX_RELEASE) {
			game->key_s_pressed = 0;
		}
	}
	if (keydata.key == MLX_KEY_D) {
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
			game->key_d_pressed = 1;
		}
		if (keydata.action == MLX_RELEASE) {
			game->key_d_pressed = 0;
		}
	}
	if (keydata.key == MLX_KEY_A) {
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
			game->key_a_pressed = 1;
		}
		if (keydata.action == MLX_RELEASE) {
			game->key_a_pressed = 0;
		}
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		{
			game->key_left_pressed = 1;
		}
		if (keydata.action == MLX_RELEASE)
		{
			game->key_left_pressed = 0;
		}
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		{
			game->key_right_pressed = 1;
		}
		else if (keydata.action == MLX_RELEASE)
		{
			game->key_right_pressed = 0;
		}
	}
	
	float dx = 0.0f;
	float dy = 0.0f;

	if (game->key_left_pressed) {
		game->player_rotation_angle -= 0.1;
	}
	if (game->key_right_pressed) {
		game->player_rotation_angle += 0.1;
	}
	
	if (game->key_w_pressed) {
		dy -= move_speed * sinf(game->player_rotation_angle);
		dx -= move_speed * cosf(game->player_rotation_angle);
	}

	if (game->key_s_pressed) {
		dy += move_speed * sinf(game->player_rotation_angle);
		dx += move_speed * cosf(game->player_rotation_angle);
	}

	if (game->key_a_pressed) {
		dx += move_speed * cosf(game->player_rotation_angle + M_PI_2);
		dy += move_speed * sinf(game->player_rotation_angle + M_PI_2);
	}

	if (game->key_d_pressed) {
		dx -= move_speed * cosf(game->player_rotation_angle + M_PI_2);
		dy -= move_speed * sinf(game->player_rotation_angle + M_PI_2);
	}

	// Aktualisiere die Spielerposition basierend auf 
	der kombinierten Bewegung
	game->player_x += dx;
	game->player_y += dy;

}

#endif 
*/