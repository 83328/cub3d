/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_commands_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:43:29 by ohoro             #+#    #+#             */
/*   Updated: 2024/06/24 15:21:16 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_rotation(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT && (keydata.action 
			== MLX_PRESS || keydata.action == MLX_REPEAT))
		game->player_rotation_angle -= 0.1;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action 
			== MLX_PRESS || keydata.action == MLX_REPEAT))
		game->player_rotation_angle += 0.1;
}

void	move_forward(t_game *game, float move_speed)
{
	float dy = -move_speed * sinf(game->player_rotation_angle);
	float dx = -move_speed * cosf(game->player_rotation_angle);
	update_player_position(game, dx, dy);
}

void	move_backward(t_game *game, float move_speed)
{
	float dy = move_speed * sinf(game->player_rotation_angle);
	float dx = move_speed * cosf(game->player_rotation_angle);
	update_player_position(game, dx, dy);
}

void	move_left(t_game *game, float move_speed)
{
	float dx = move_speed * cosf(game->player_rotation_angle + M_PI_2);
	float dy = move_speed * sinf(game->player_rotation_angle + M_PI_2);
	update_player_position(game, dx, dy);
}

void	move_right(t_game *game, float move_speed)
{
	float dx = -move_speed * cosf(game->player_rotation_angle + M_PI_2);
	float dy = -move_speed * sinf(game->player_rotation_angle + M_PI_2);
	update_player_position(game, dx, dy);
}
