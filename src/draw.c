/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:52:14 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/24 15:04:17 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(void *param)
{
	t_game	*game;
	int		x;
	int		y;

	game = (t_game *)param;
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

void	draw_all_and_clear(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	clear_image(game);
	redraw_player(game);
	cast_all_rays(game);
	wall_projection(game);
	draw_minimap(game);
	cast_all_rays(game);
}
