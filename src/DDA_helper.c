/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:35:09 by ohoro             #+#    #+#             */
/*   Updated: 2024/06/26 14:11:26 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_ray_facing_down(float angle)
{
	return (angle > 0 && angle < PI);
}

int	is_ray_facing_up(float angle)
{
	return (angle > PI && angle < TWO_PI);
}

int	is_ray_facing_right(float angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}

int	is_ray_facing_left(float angle)
{
	return (angle > 0.5 * PI && angle < 1.5 * PI);
}

void	dda_init(t_dda *dda, t_game *game, int i)
{
	dda->is_ray_facing_down = is_ray_facing_down(game->rays[i].ray_angle);
	dda->is_ray_facing_up = is_ray_facing_up(game->rays[i].ray_angle);
	dda->is_ray_facing_right = is_ray_facing_right(game->rays[i].ray_angle);
	dda->is_ray_facing_left = is_ray_facing_left(game->rays[i].ray_angle);
}

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

void	handle_wall_hit(t_game *game, t_dda *dda, 
	float x_to_check, float y_to_check)
{
	if (has_wall_at(*game, x_to_check, y_to_check))
	{
		// Found a wall hit
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

void	handle_vertical_wall_hit(t_game *game, t_dda *dda, 
	float x_to_check, float y_to_check)
{
	if (has_wall_at(*game, x_to_check, y_to_check))
	{
		// Found a wall hit
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

/* void	dda_loop_vertical(t_game *game, t_dda *dda)
{
	while (dda->next_vert_touch_x >= 0 && 
		dda->next_vert_touch_x <= game->map_cols * TILE_SIZE && 
			dda->next_vert_touch_y >= 0 && dda->next_vert_touch_y <= game->map_rows * TILE_SIZE)
	{
		float x_to_check = dda->next_vert_touch_x + (dda->is_ray_facing_left ? -1 : 0);
		float y_to_check = dda->next_vert_touch_y;

		if (has_wall_at(*game, x_to_check, y_to_check))
		{
			// found a wall hit
			dda->vert_wall_hit_x = dda->next_vert_touch_x;
			dda->vert_wall_hit_y = dda->next_vert_touch_y;
			dda->vert_wall_content = game->map_grid_2d[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			dda->found_vert_wall_hit = true;
			break ;
		}
		else
		{
			dda->next_vert_touch_x += dda->xstep;
			dda->next_vert_touch_y += dda->ystep;
		}
	}
} */

void	calculate_nearest_intersection(t_game *game, t_dda *dda, int i)
{
	float horz_hit_distance = dda->found_horz_wall_hit
		? distance_between_points(game->player_x, game->player_y, dda->horz_wall_hit_x, dda->horz_wall_hit_y)
		: FLT_MAX;
	float vert_hit_distance = dda->found_vert_wall_hit
		? distance_between_points(game->player_x, game->player_y, dda->vert_wall_hit_x, dda->vert_wall_hit_y)
		: FLT_MAX;

	if (vert_hit_distance < horz_hit_distance)
	{
		game->rays[i].distance = vert_hit_distance;
		game->rays[i].wall_hit_x = dda->vert_wall_hit_x;
		game->rays[i].wall_hit_y = dda->vert_wall_hit_y;
		game->rays[i].wall_hit_content = dda->vert_wall_content;
		game->rays[i].was_hit_vertical = true;
	}
	else
	{
		game->rays[i].distance = horz_hit_distance;
		game->rays[i].wall_hit_x = dda->horz_wall_hit_x;
		game->rays[i].wall_hit_y = dda->horz_wall_hit_y;
		game->rays[i].wall_hit_content = dda->horz_wall_content;
		game->rays[i].was_hit_vertical = false;
	}
}

void	draw_this_ray(t_game *game, int i)
{
	t_line line;
	line.x0 = game->player_x;
	line.y0 = game->player_y;
	line.x1 = game->rays[i].wall_hit_x;
	line.y1 = game->rays[i].wall_hit_y;
	bresenham(line, game->image);
}

void	horizontal_and_vertical_grid_intersection(t_game *game, int i)
{
	t_dda	dda;
	
	dda_init(&dda, game, i);
	dda_init_for_horizontal(&dda, game, i);
	dda_loop_horizontal(game, &dda);
	dda_init_for_vertical(&dda, game, i);
	dda_loop_vertical(game, &dda);
	calculate_nearest_intersection(game, &dda, i);
	draw_this_ray(game, i);
}
