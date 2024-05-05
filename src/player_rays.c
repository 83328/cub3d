/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:23:15 by ohoro             #+#    #+#             */
/*   Updated: 2024/05/05 11:45:49 by ohoro            ###   ########.fr       */
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
	 for (int i = 0; i < 42; i++)
	 {
		 game->rays[i].ray_angle = game->player_rotation_angle - (FOV_ANGLE / 2) + (FOV_ANGLE / 42) * i;
		 normalize_angle(&game->rays[i].ray_angle);
		 horizontal_and_vertical_grid_intersection(game, i);
	 }
	
 }