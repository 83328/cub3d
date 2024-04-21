/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:08:58 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/21 18:17:49 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	erase_old_player(t_game *game)
{
	erase_pixel(game->player_x, game->player_y, game->image);
}

void	draw_new_player(t_game *game)
{
	put_pixel(game->player_x, game->player_y, game->image);
}

void	update_player(t_game *game)
{
	if (game->key_w_pressed)
		game->player_y -= 1;
	if (game->key_s_pressed)
		game->player_y += 1;
	if (game->key_a_pressed)
		game->player_x -= 1;
	if (game->key_d_pressed)
		game->player_x += 1;
	if (game->key_left_pressed)
		game->player_rotation_angle -= 0.1;
	if (game->key_right_pressed)
		game->player_rotation_angle += 0.1;
}

void redraw_player(void *param)
{
	t_game *game;

	game = (t_game *)param;
    erase_old_player(game);
	update_player(game);
	draw_new_player(game);
	reset_keys(game);	
}