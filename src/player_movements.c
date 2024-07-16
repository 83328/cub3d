/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:08:58 by ohoro             #+#    #+#             */
/*   Updated: 2024/07/16 14:36:53 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	erase_old_player(t_game *game)
{
	erase_pixel(game->player_x, game->player_y, game->image);
}

void	draw_new_player(t_game *game)
{
	// draw player only if it is inside the screen
	if (game->player_x >= 0 && game->player_x < WIDTH 
		&& game->player_y >= 0 && game->player_y < HEIGHT)
		put_pixel(game->player_x, game->player_y, game->image);
}

void	redraw_player(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_new_player(game);
	//draw_player_middle_ray(game);
}
