/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:35:09 by ohoro             #+#    #+#             */
/*   Updated: 2024/05/05 11:35:53 by ohoro            ###   ########.fr       */
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

float distance_between_points(float x1, float y1, float x2, float y2)
{
    return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}



void horizontal_and_vertical_grid_intersection(t_game *game, int i)
{
    int isRayFacingDown = game->rays[i].ray_angle > 0 && game->rays[i].ray_angle < PI;
    int isRayFacingUp = !isRayFacingDown;

    int isRayFacingRight =  game->rays[i].ray_angle < 0.5 * PI ||  game->rays[i].ray_angle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;

    float xintercept, yintercept;
    float xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    bool foundHorzWallHit = false;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(game->player_y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDown ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = game->player_x + (yintercept - game->player_y) / tan( game->rays[i].ray_angle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan( game->rays[i].ray_angle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= HEIGHT) {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

        if (has_wall_at(*game, xToCheck, yToCheck)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallContent = game->map_grid[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = true;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundVertWallHit = false;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    int vertWallContent = 0;

    // Find the x-coordinate of the closest vertical grid intersection
    xintercept = floor(game->player_x/ TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest vertical grid intersection
    yintercept = game->player_y + (xintercept - game->player_x) * tan( game->rays[i].ray_angle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan( game->rays[i].ray_angle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= HEIGHT) {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;

        if (has_wall_at(*game, xToCheck, yToCheck)) {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            vertWallContent = game->map_grid[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = true;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    // Calculate both horizontal and vertical hit distances and choose the smallest one
    float horzHitDistance = foundHorzWallHit
        ? distance_between_points(game->player_x, game->player_y, horzWallHitX, horzWallHitY)
        : FLT_MAX;
    float vertHitDistance = foundVertWallHit
        ? distance_between_points(game->player_x, game->player_y, vertWallHitX, vertWallHitY)
        : FLT_MAX;

    if (vertHitDistance < horzHitDistance) {
        game->rays[i].distance = vertHitDistance;
        game->rays[i].wall_hit_x = vertWallHitX;
        game->rays[i].wall_hit_y = vertWallHitY;
        game->rays[i].wall_hit_content = vertWallContent;
        game->rays[i].was_hit_vertical = true;
    } else {
        game->rays[i].distance = horzHitDistance;
        game->rays[i].wall_hit_x = horzWallHitX;
        game->rays[i].wall_hit_y = horzWallHitY;
        game->rays[i].wall_hit_content = horzWallContent;
        game->rays[i].was_hit_vertical = false;
    }
    game->rays[i].ray_angle =  game->rays[i].ray_angle;
    game->rays[i].is_ray_facing_down = isRayFacingDown;
    game->rays[i].is_ray_facing_up = isRayFacingUp;
    game->rays[i].is_ray_facing_left = isRayFacingLeft;
    game->rays[i].is_ray_facing_right = isRayFacingRight;

    t_line line;
    line.x0 = game->player_x;
    line.y0 = game->player_y;
    line.x1 = game->rays[i].wall_hit_x;
    line.y1 = game->rays[i].wall_hit_y;
    bresenham(line, game->image);
}
