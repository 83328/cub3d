/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:55 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/23 19:06:40 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void handle_movement_and_rotation_keys(mlx_key_data_t keydata, t_game *game)
{
float move_speed = 2.0f;
    if (keydata.key == MLX_KEY_W) {
        if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
            game->key_w_pressed = 1;
        } else if (keydata.action == MLX_RELEASE) {
            game->key_w_pressed = 0;
        }
    }
    if (keydata.key == MLX_KEY_S) {
        if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
            game->key_s_pressed = 1;
        } else if (keydata.action == MLX_RELEASE) {
            game->key_s_pressed = 0;
        }
    }
    if (keydata.key == MLX_KEY_D) {
        if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
            game->key_d_pressed = 1;
        } else if (keydata.action == MLX_RELEASE) {
            game->key_d_pressed = 0;
        }
    }
    if (keydata.key == MLX_KEY_A) {
        if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
            game->key_a_pressed = 1;
        } else if (keydata.action == MLX_RELEASE) {
            game->key_a_pressed = 0;
        }
    }
	if (keydata.key == MLX_KEY_LEFT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		{
			game->key_left_pressed = 1;
		}
		else if (keydata.action == MLX_RELEASE)
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

    // Aktualisiere die Spielerposition basierend auf der kombinierten Bewegung
    game->player_x += dx;
    game->player_y += dy;

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
	handle_movement_and_rotation_keys(keydata, game);
	handle_escape_key(keydata);
}
