/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_2_horizontal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:17:05 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/27 11:28:09 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_init_for_horizontal(t_dda *dda, t_game *game, int i)
{
	dda->found_horz_wall_hit = false;
	dda->horz_wall_hit_x = 0;
	dda->horz_wall_hit_y = 0;
	dda->horz_wall_content = 0;
	dda->yintercept = floor(game->player_y / TILE_SIZE) * TILE_SIZE;
	if (dda->is_ray_facing_down)
		dda->yintercept += TILE_SIZE;
	dda->xintercept = game->player_x + 
		(dda->yintercept - game->player_y) / tan(game->rays[i].ray_angle);
	dda->ystep = TILE_SIZE;
	if (dda->is_ray_facing_up)
	{
		dda->ystep *= -1;
	}
	dda->xstep = TILE_SIZE / tan(game->rays[i].ray_angle);
	if (dda->is_ray_facing_left && dda->xstep > 0)
	{
		dda->xstep *= -1;
	}
	if (dda->is_ray_facing_right && dda->xstep < 0)
	{
		dda->xstep *= -1;
	}
	dda->next_horz_touch_x = dda->xintercept;
	dda->next_horz_touch_y = dda->yintercept;
}

void	handle_wall_hit(t_game *game, t_dda *dda, 
	float x_to_check, float y_to_check)
{
	if (has_wall_at(*game, x_to_check, y_to_check))
	{
		dda->horz_wall_hit_x = dda->next_horz_touch_x;
		dda->horz_wall_hit_y = dda->next_horz_touch_y;
		dda->horz_wall_content = game->map_grid_2d[(int)floor(y_to_check / 
				TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
		dda->found_horz_wall_hit = true;
	}
	else
	{
		dda->next_horz_touch_x += dda->xstep;
		dda->next_horz_touch_y += dda->ystep;
	}
}

void	dda_loop_horizontal(t_game *game, t_dda *dda)
{
	float	x_to_check;
	float	y_to_check;

	while (dda->next_horz_touch_x >= 0 && 
		dda->next_horz_touch_x <= game->map_cols * TILE_SIZE && 
		dda->next_horz_touch_y >= 0 && 
		dda->next_horz_touch_y <= game->map_rows * TILE_SIZE)
	{
		x_to_check = dda->next_horz_touch_x;
		if (dda->is_ray_facing_up)
		{
			y_to_check = dda->next_horz_touch_y - 1;
		}
		else
		{
			y_to_check = dda->next_horz_touch_y;
		}
		handle_wall_hit(game, dda, x_to_check, y_to_check);
		if (dda->found_horz_wall_hit)
		{
			break ;
		}
	}
}
