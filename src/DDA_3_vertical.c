/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA-3_vertical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:21:31 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/27 11:28:49 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_init_for_vertical(t_dda *dda, t_game *game, int i)
{
	dda->found_vert_wall_hit = false;
	dda->vert_wall_hit_x = 0;
	dda->vert_wall_hit_y = 0;
	dda->vert_wall_content = 0;
	dda->xintercept = floor(game->player_x / TILE_SIZE) * TILE_SIZE;
	if (dda->is_ray_facing_right)
		dda->xintercept += TILE_SIZE;
	dda->yintercept = game->player_y + (dda->xintercept - game->player_x) 
		* tan(game->rays[i].ray_angle);
	dda->xstep = TILE_SIZE;
	if (dda->is_ray_facing_left)
		dda->xstep *= -1;
	else
		dda->xstep *= 1;
	dda->ystep = TILE_SIZE * tan(game->rays[i].ray_angle);
	if (dda->is_ray_facing_up && dda->ystep > 0)
		dda->ystep *= -1;
	else if (dda->is_ray_facing_down && dda->ystep < 0)
		dda->ystep *= -1;
	else
		dda->ystep *= 1;
	dda->next_vert_touch_x = dda->xintercept;
	dda->next_vert_touch_y = dda->yintercept;
}

void	handle_vertical_wall_hit(t_game *game, t_dda *dda, 
	float x_to_check, float y_to_check)
{
	if (has_wall_at(*game, x_to_check, y_to_check))
	{
		dda->vert_wall_hit_x = dda->next_vert_touch_x;
		dda->vert_wall_hit_y = dda->next_vert_touch_y;
		dda->vert_wall_content = game->map_grid_2d[(int)floor(y_to_check / 
				TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
		dda->found_vert_wall_hit = true;
	}
	else
	{
		dda->next_vert_touch_x += dda->xstep;
		dda->next_vert_touch_y += dda->ystep;
	}
}

void	dda_loop_vertical(t_game *game, t_dda *dda)
{
	float	x_to_check;
	float	y_to_check;

	while (dda->next_vert_touch_x >= 0 && 
		dda->next_vert_touch_x <= game->map_cols * TILE_SIZE && 
		dda->next_vert_touch_y >= 0 && 
		dda->next_vert_touch_y <= game->map_rows * TILE_SIZE)
	{
		if (dda->is_ray_facing_left)
		{
			x_to_check = dda->next_vert_touch_x - 1;
		}
		else
		{
			x_to_check = dda->next_vert_touch_x;
		}
		y_to_check = dda->next_vert_touch_y;
		handle_vertical_wall_hit(game, dda, x_to_check, y_to_check);
		if (dda->found_vert_wall_hit)
		{
			break ;
		}
	}
}
