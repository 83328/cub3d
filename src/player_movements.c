/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:08:58 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/23 19:14:53 by ohoro            ###   ########.fr       */
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
	if (game->player_x >= 0 && game->player_x < WIDTH && game->player_y >= 0 && game->player_y < HEIGHT)    
		put_pixel(game->player_x, game->player_y, game->image);
}


void clear_image(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			erase_pixel(x, y, game->image);
			x++;
		}
		y++;
	}
}

void	redraw_player(void *param)
{
	t_game *game;

	game = (t_game *)param;
  
	clear_image(game);
	draw_new_player(game);
	draw_player_middle_ray(game);	
}