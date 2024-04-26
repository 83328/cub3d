/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:23:15 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/26 12:08:25 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "cub3d.h"

void	draw_player_middle_ray(t_game *game)
{
	t_line line;

	line.x0 = game->player_x;
	line.y0 = game->player_y;
	line.x1 = game->player_x + cos(game->player_rotation_angle) * 24;
	line.y1 = game->player_y + sin(game->player_rotation_angle) * 24;
	bresenham(line, game->image);
}

void cast_all_rays(void *param)
 {
	t_game *game;
	game = (t_game *)param;
	 for (int i = 0; i < WIDTH; i++)
	 {
		 game->rays[i].ray_angle = game->player_rotation_angle - (FOV_ANGLE / 2) + (FOV_ANGLE / WIDTH) * i;
		 printf("Ray %d: %f\n", i, game->rays[i].ray_angle);
		 t_line line;
		 line.x0 = game->player_x;
		 line.y0 = game->player_y;
		 line.x1 = game->player_x + cos(game->rays[i].ray_angle) * 30;
		 line.y1 = game->player_y + sin(game->rays[i].ray_angle) * 30;
		 bresenham(line, game->image);
	 }
	
 }