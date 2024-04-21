/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:23:15 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/21 18:26:12 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "cub3d.h"

void draw_player_middle_ray(t_game *game)
{
    t_line line;

    line.x0 = game->player_x;
    line.y0 = game->player_y;
    line.x1 = game->player_x + cos(game->player_rotation_angle) * 100;
    line.y1 = game->player_y + sin(game->player_rotation_angle) * 100;
    bresenham(line, game->image);
}

