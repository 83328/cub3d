/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:35:09 by ohoro             #+#    #+#             */
/*   Updated: 2024/06/27 11:23:38 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_distances(t_game *game, t_dda *dda, 
	float *horz_hit_distance, float *vert_hit_distance)
{
	if (dda->found_horz_wall_hit)
	{
		*horz_hit_distance = distance_between_points(game->player_x, 
				game->player_y, dda->horz_wall_hit_x, dda->horz_wall_hit_y);
	}
	else
	{
		*horz_hit_distance = FLT_MAX;
	}
	if (dda->found_vert_wall_hit)
	{
		*vert_hit_distance = distance_between_points(game->player_x, 
				game->player_y, dda->vert_wall_hit_x, dda->vert_wall_hit_y);
	}
	else
	{
		*vert_hit_distance = FLT_MAX;
	}
}

void	assign_ray_values(t_game *game, t_dda *dda, int i, 
	t_distances *distances)
{
	if (distances->vert_hit_distance < distances->horz_hit_distance)
	{
		game->rays[i].distance = distances->vert_hit_distance;
		game->rays[i].wall_hit_x = dda->vert_wall_hit_x;
		game->rays[i].wall_hit_y = dda->vert_wall_hit_y;
		game->rays[i].wall_hit_content = dda->vert_wall_content;
		game->rays[i].was_hit_vertical = true;
	}
	else
	{
		game->rays[i].distance = distances->horz_hit_distance;
		game->rays[i].wall_hit_x = dda->horz_wall_hit_x;
		game->rays[i].wall_hit_y = dda->horz_wall_hit_y;
		game->rays[i].wall_hit_content = dda->horz_wall_content;
		game->rays[i].was_hit_vertical = false;
	}
}

void	calculate_nearest_intersection(t_game *game, t_dda *dda, int i)
{
	t_distances	distances;

	calculate_distances(game, dda, &distances.horz_hit_distance, 
		&distances.vert_hit_distance);
	assign_ray_values(game, dda, i, &distances);
}

void	draw_this_ray(t_game *game, int i)
{
	t_line	line;

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
