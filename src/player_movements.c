/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:08:58 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/21 19:49:04 by ohoro            ###   ########.fr       */
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
   #if 0
    erase_old_player(game);
   	update_player(game);
    draw_new_player(game);
	reset_keys(game);
    #endif
    mlx_delete_image(game->mlx, game->image);
    game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    update_player(game);
    draw_new_player(game);
    mlx_image_to_window(game->mlx, game->image, 0, 0);
    reset_keys(game);	
}