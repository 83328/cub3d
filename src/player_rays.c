/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:23:15 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/23 17:30:41 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "cub3d.h"

void	draw_player_middle_ray(t_game *game)
{
	t_line line;

	line.x0 = game->player_x;
	line.y0 = game->player_y;
	line.x1 = game->player_x + cos(game->player_rotation_angle) * 100;
	line.y1 = game->player_y + sin(game->player_rotation_angle) * 100;
	bresenham(line, game->image);
}
