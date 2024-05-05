/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:35:09 by ohoro             #+#    #+#             */
/*   Updated: 2024/05/05 13:58:35 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_ray_facing_down(float angle)
{
	return (angle > 0 && angle < PI);
}

int is_ray_facing_up(float angle)
{
	return (angle > PI && angle < TWO_PI);
}

int is_ray_facing_right(float angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}

int is_ray_facing_left(float angle)
{
	return (angle > 0.5 * PI && angle < 1.5 * PI);
}

void dda_init(t_dda *dda, t_game *game, int i)
{
    dda->is_ray_facing_down = is_ray_facing_down(game->rays[i].ray_angle);
    dda->is_ray_facing_up = is_ray_facing_up(game->rays[i].ray_angle);
    dda->is_ray_facing_right = is_ray_facing_right(game->rays[i].ray_angle);
    dda->is_ray_facing_left = is_ray_facing_left(game->rays[i].ray_angle);

}

void dda_init_for_horizontal(t_dda *dda, t_game *game, int i)
{
    dda->found_horz_wall_hit = false;
    dda->horz_wall_hit_x = 0;
    dda->horz_wall_hit_y = 0;
    dda->horz_wall_content = 0;  
    dda->yintercept = floor(game->player_y / TILE_SIZE) * TILE_SIZE;
    dda->yintercept += dda->is_ray_facing_down ? TILE_SIZE : 0;
    dda->xintercept = game->player_x + (dda->yintercept - game->player_y) / tan( game->rays[i].ray_angle);
    dda->ystep = TILE_SIZE;
    dda->ystep *= dda->is_ray_facing_up ? -1 : 1;
    dda->xstep = TILE_SIZE / tan( game->rays[i].ray_angle);
    dda->xstep *= (dda->is_ray_facing_left && dda->xstep > 0) ? -1 : 1;
    dda->xstep *= (dda->is_ray_facing_right && dda->xstep < 0) ? -1 : 1;
    dda->next_horz_touch_x = dda->xintercept;
    dda->next_horz_touch_y = dda->yintercept;
}

void dda_init_for_vertical(t_dda *dda, t_game *game, int i)
{
    dda->found_vert_wall_hit = false;
    dda->vert_wall_hit_x = 0;
    dda->vert_wall_hit_y = 0;
    dda->vert_wall_content = 0;
    dda->xintercept = floor(game->player_x / TILE_SIZE) * TILE_SIZE;
    dda->xintercept += dda->is_ray_facing_right ? TILE_SIZE : 0;
    dda->yintercept = game->player_y + (dda->xintercept - game->player_x) * tan( game->rays[i].ray_angle);
    dda->xstep = TILE_SIZE;
    dda->xstep *= dda->is_ray_facing_left ? -1 : 1;
    dda->ystep = TILE_SIZE * tan( game->rays[i].ray_angle);
    dda->ystep *= (dda->is_ray_facing_up && dda->ystep > 0) ? -1 : 1;
    dda->ystep *= (dda->is_ray_facing_down && dda->ystep < 0) ? -1 : 1;
    dda->next_vert_touch_x = dda->xintercept;
    dda->next_vert_touch_y = dda->yintercept;
}

void dda_loop_horizontal(t_game *game, t_dda *dda)
{
    while (dda->next_horz_touch_x >= 0 && dda->next_horz_touch_x <= WIDTH && dda->next_horz_touch_y >= 0 && dda->next_horz_touch_y <= HEIGHT) {
        float xToCheck = dda->next_horz_touch_x;
        float yToCheck = dda->next_horz_touch_y + (dda->is_ray_facing_up ? -1 : 0);

        if (has_wall_at(*game, xToCheck, yToCheck)) {
            // found a wall hit
            dda->horz_wall_hit_x = dda->next_horz_touch_x;
            dda->horz_wall_hit_y = dda->next_horz_touch_y;
            dda->horz_wall_content = game->map_grid[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            dda->found_horz_wall_hit = true;
            break;
        } else {
            dda->next_horz_touch_x += dda->xstep;
            dda->next_horz_touch_y += dda->ystep;
        }
    }
}

void dda_loop_vertical(t_game *game, t_dda *dda)
{
    while (dda->next_vert_touch_x >= 0 && dda->next_vert_touch_x <= WIDTH && dda->next_vert_touch_y >= 0 && dda->next_vert_touch_y <= HEIGHT) {
        float xToCheck = dda->next_vert_touch_x + (dda->is_ray_facing_left ? -1 : 0);
        float yToCheck = dda->next_vert_touch_y;

        if (has_wall_at(*game, xToCheck, yToCheck)) {
            // found a wall hit
            dda->vert_wall_hit_x = dda->next_vert_touch_x;
            dda->vert_wall_hit_y = dda->next_vert_touch_y;
            dda->vert_wall_content = game->map_grid[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            dda->found_vert_wall_hit = true;
            break;
        } else {
            dda->next_vert_touch_x += dda->xstep;
            dda->next_vert_touch_y += dda->ystep;
        }
    }

}

void calculate_nearest_intersection(t_game *game, t_dda *dda, int i)
{
    float horzHitDistance = dda->found_horz_wall_hit
        ? distance_between_points(game->player_x, game->player_y, dda->horz_wall_hit_x, dda->horz_wall_hit_y)
        : FLT_MAX;
    float vertHitDistance = dda->found_vert_wall_hit
        ? distance_between_points(game->player_x, game->player_y, dda->vert_wall_hit_x, dda->vert_wall_hit_y)
        : FLT_MAX;

    if (vertHitDistance < horzHitDistance) {
        game->rays[i].distance = vertHitDistance;
        game->rays[i].wall_hit_x = dda->vert_wall_hit_x;
        game->rays[i].wall_hit_y = dda->vert_wall_hit_y;
        game->rays[i].wall_hit_content = dda->vert_wall_content;
        game->rays[i].was_hit_vertical = true;
    } else {
        game->rays[i].distance = horzHitDistance;
        game->rays[i].wall_hit_x = dda->horz_wall_hit_x;
        game->rays[i].wall_hit_y = dda->horz_wall_hit_y;
        game->rays[i].wall_hit_content = dda->horz_wall_content;
        game->rays[i].was_hit_vertical = false;
    }
}

void draw_this_ray(t_game *game, int i)
{
    t_line line;
    line.x0 = game->player_x;
    line.y0 = game->player_y;
    line.x1 = game->rays[i].wall_hit_x;
    line.y1 = game->rays[i].wall_hit_y;
    bresenham(line, game->image);
}

void horizontal_and_vertical_grid_intersection(t_game *game, int i)
{
    t_dda dda;
    
    dda_init(&dda, game, i);
    dda_init_for_horizontal(&dda, game, i);
    dda_loop_horizontal(game, &dda);
    dda_init_for_vertical(&dda, game, i);
    dda_loop_vertical(game, &dda);
    calculate_nearest_intersection(game, &dda, i);
    draw_this_ray(game, i);
}
