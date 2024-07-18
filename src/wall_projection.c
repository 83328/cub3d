/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:27:21 by ohoro             #+#    #+#             */
/*   Updated: 2024/07/18 15:54:18 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_projection(t_game *game, int x, t_wall_projection *wp)
{
	float	perp_distance;
	float	projected_wall_height;

	perp_distance = game->rays[x].distance * 
		cos(game->rays[x].ray_angle - game->player_rotation_angle);
	projected_wall_height = (TILE_SIZE / perp_distance) * 
		DIST_PROJ_PLANE;
	wp->wall_strip_height = (int)projected_wall_height;
	wp->wall_top_pixel = (WINDOW_HEIGHT / 2) 
		- (wp->wall_strip_height / 2);
	if (wp->wall_top_pixel < 0)
	{
		wp->wall_top_pixel = 0;
	}
	wp->wall_bottom_pixel = (WINDOW_HEIGHT / 2) 
		+ (wp->wall_strip_height / 2);
	if (wp->wall_bottom_pixel > WINDOW_HEIGHT)
	{
		wp->wall_bottom_pixel = WINDOW_HEIGHT;
	}
}

void	draw_ceiling(t_game *game, int x, int wall_top_pixel)
{
	int	y;
	int	color;

	y = 0;
	while (y < wall_top_pixel)
	{
		//color = get_rgba(68, 68, 68, 255);
		color = game->ceiling_color;
		reverse_bits((uint32_t *)&color);
		our_mlx_put_pixel(game->image, x, y, color);
		y++;
	}
}

void	draw_wall(t_game *game, int x, t_wall_projection *wp)
{
	t_wall_draw	wd;

	wd.y = wp->wall_top_pixel;
	if (game->rays[x].was_hit_vertical)
		wd.texture_offset_x = (int)game->rays[x].wall_hit_y % TILE_SIZE;
	else
		wd.texture_offset_x = (int)game->rays[x].wall_hit_x % TILE_SIZE;
	select_texture(&game->rays[x], game);
	wd.texture_height = game->north_texture->height;
	while (wd.y < wp->wall_bottom_pixel)
	{
		wd.distance_from_top = wd.y + (wp->wall_strip_height / 2) 
			- (WINDOW_HEIGHT / 2);
		wd.texture_offset_y = wd.distance_from_top 
			* ((float)wd.texture_height / wp->wall_strip_height);
		game->rays[x].current_texture_image 
			= return_texture_image(&game->rays[x]);
		wd.texel_color = put_pixel_color(game->rays[x].current_texture_image, 
				wd.texture_offset_x, wd.texture_offset_y);
		reverse_bits(&wd.texel_color);
		our_mlx_put_pixel(game->image, x, wd.y, wd.texel_color);
		wd.y++;
	}
}

/* int parse_rgb_from_string(const char *color_str, int *r, int *g, int *b)
{
	return sscanf(color_str, "%d,%d,%d", r, g, b) == 3;
}

void draw_floor(t_game *game, int x, int wall_bottom_pixel)
{
	int y;
	int floor_color;
	int r, g, b;

	if (parse_rgb_from_string(game->floor_color_str, &r, &g, &b))
	{
		floor_color = get_rgba(r, g, b, 255);
	}
	else
	{
		//floor_color = get_rgba(220, 100, 0, 255);
		floor_color = get_rgba(220, 100, 0, 255);
		ft_error(ERR_FLOOR_COLOR, NULL);
	}
	y = wall_bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		reverse_bits((uint32_t *)&floor_color);
		our_mlx_put_pixel(game->image, x, y, floor_color);
		y++;
	}
} */

void	draw_floor(t_game *game, int x, int wall_bottom_pixel)
{
	int	y;
	int	floor_color;

	y = wall_bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		//floor_color = get_rgba(136, 66, 136, 255);
		//floor_color = get_rgba(220, 100, 0, 255);
		floor_color = game->floor_color;
		reverse_bits((uint32_t *)&floor_color);
		our_mlx_put_pixel(game->image, x, y, floor_color);
		y++;
	}
}

void	wall_projection(t_game *game)
{
	int					x;
	t_wall_projection	wp;

	x = 0;
	while (x < NUM_RAYS)
	{
		calculate_wall_projection(game, x, &wp);
		draw_ceiling(game, x, wp.wall_top_pixel);
		draw_wall(game, x, &wp);
		draw_floor(game, x, wp.wall_bottom_pixel);
		x++;
	}
}
