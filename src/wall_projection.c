/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:27:21 by ohoro             #+#    #+#             */
/*   Updated: 2024/06/26 17:05:24 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	put_pixel_color(mlx_image_t *img, int x, int y)
{
	uint32_t	*px;

	px = (uint32_t *)(img->pixels + (img->width * y + x) * sizeof(uint32_t));
	return (*px);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

int	get_a(int rgba)
{
	return (rgba & 0xFF);
}

void	convert_rgba_to_abgr(uint32_t *color)
{
	*color = (*color >> 24)
		| ((*color << 8) & 0x00FF0000)
		| ((*color >> 8) & 0x0000FF00)
		| (*color << 24);
}

void	our_mlx_draw_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	our_mlx_put_pixel(mlx_image_t *image, uint32_t x, 
	uint32_t y, uint32_t color)
{
	uint8_t	*pixelstart;

	pixelstart = &image->pixels[(y * image->width + x) * sizeof(int32_t)];
	our_mlx_draw_pixel(pixelstart, color);
}

void	load_test_texture_north(t_game *game)
{
	game->north_texture = mlx_load_png("textures/32_tri.png");
	game->image_north_texture = 
		mlx_texture_to_image(game->mlx, game->north_texture);
}

void	load_test_texture_south(t_game *game)
{
	game->south_texture = mlx_load_png("textures/32_bronto.png");
	game->image_south_texture = 
		mlx_texture_to_image(game->mlx, game->south_texture);
}

void	load_test_texture_west(t_game *game)
{
	game->west_texture = mlx_load_png("textures/32_ptero.png");
	game->image_west_texture = 
		mlx_texture_to_image(game->mlx, game->west_texture);
}

void	load_test_texture_east(t_game *game)
{
	game->east_texture = mlx_load_png("textures/32_tyr.png");
	game->image_east_texture = 
		mlx_texture_to_image(game->mlx, game->east_texture);
}

void	select_texture(t_ray *ray, t_game *game)
{
	float	angle;

	angle = ray->ray_angle;
	normalize_angle(&angle);
	if (ray->was_hit_vertical)
	{
		if (angle >= M_PI / 2 && angle < 3 * M_PI / 2)
		{
			ray->current_texture = game->west_texture;
			ray->current_texture_image = game->image_west_texture;
		}
		else
		{
			ray->current_texture = game->east_texture;
			ray->current_texture_image = game->image_east_texture;
		}
	}
	else
	{
		if (angle >= 0 && angle < M_PI)
		{
			ray->current_texture = game->south_texture;
			ray->current_texture_image = game->image_south_texture;
		}
		else
		{
			ray->current_texture = game->north_texture;
			ray->current_texture_image = game->image_north_texture;
		}
	}
}

mlx_image_t	*return_texture_image(t_ray *ray)
{
	return (ray->current_texture_image);
}

void	reverse_bits(uint32_t *color)
{
	*color = (*color >> 24)
		| ((*color << 8) & 0x00FF0000)
		| ((*color >> 8) & 0x0000FF00)
		| (*color << 24);
}

void	project_test_texture_north(void *param)
{
	t_game		*game;
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	game = (t_game *)param;
	x = 0;
	y = 0;
	while (y < game->image_north_texture->width)
	{
		while (x < game->image_north_texture->height)
		{
			color = put_pixel_color(game->image_north_texture, x, y);
			reverse_bits(&color);
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_wall_strip_green(int x, int y, int width, int height, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			mlx_put_pixel(game->image, x + j, y + i, 0x00FF00);
			j++;
		}
		i++;
	}
}

void	draw_strip(int x, int y, int width, int height, int color, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			mlx_put_pixel(game->image, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

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

	wp->wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wp->wall_strip_height / 2);

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
		color = get_rgba(68, 68, 68, 255);
		reverse_bits((uint32_t *)&color);
		our_mlx_put_pixel(game->image, x, y, color);
		y++;
	}
}

void	draw_wall(t_game *game, int x, int wall_top_pixel, int wall_bottom_pixel, int wall_strip_height)
{
	int			y;
	int			texture_offset_x;
	int			texture_height;
	int			distance_from_top;
	int			texture_offset_y;
	uint32_t	texel_color;

	y = wall_top_pixel;
	texture_offset_x = game->rays[x].was_hit_vertical ? (int)game->rays[x].wall_hit_y % TILE_SIZE : (int)game->rays[x].wall_hit_x % TILE_SIZE;
	select_texture(&game->rays[x], game);
	texture_height = game->north_texture->height;

	while (y < wall_bottom_pixel)
	{
		distance_from_top = y + (wall_strip_height / 2) - (WINDOW_HEIGHT / 2);
		texture_offset_y = distance_from_top * ((float)texture_height / wall_strip_height);
		game->rays[x].current_texture_image = return_texture_image(&game->rays[x]);
		texel_color = put_pixel_color(game->rays[x].current_texture_image, texture_offset_x, texture_offset_y);
		reverse_bits(&texel_color);
		our_mlx_put_pixel(game->image, x, y, texel_color);
		y++;
	}
}

void	draw_floor(t_game *game, int x, int wall_bottom_pixel)
{
	int	y = wall_bottom_pixel;
	int	floor_color;

	while (y < WINDOW_HEIGHT)
	{
		floor_color = get_rgba(136, 66, 136, 255);
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
		draw_wall(game, x, wp.wall_top_pixel, wp.wall_bottom_pixel, wp.wall_strip_height);
		draw_floor(game, x, wp.wall_bottom_pixel);
		x++;
	}
}

/* void	wall_projection(t_game *game)
{
	int			x;
	int			y;
	float		perp_distance;
	float		projected_wall_height;
	int			wall_strip_height;
	int			wall_top_pixel;
	int			wall_bottom_pixel;
	int			texture_offset_x;
	int			texture_height;
	int			distance_from_top;
	int			texture_offset_y;
	uint32_t	texel_color;
	int			color;
	int			floor_color;

	x = 0;
	while (x < NUM_RAYS)
	{
		perp_distance = game->rays[x].distance * cos(game->rays[x].ray_angle - game->player_rotation_angle);
		projected_wall_height = (TILE_SIZE / perp_distance) * DIST_PROJ_PLANE;
		wall_strip_height = (int)projected_wall_height;
		wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
		wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
		wall_bottom_pixel = wall_bottom_pixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_bottom_pixel;
		y = 0;
		while (y < wall_top_pixel)
		{
			color = get_rgba(68, 68, 68, 255);
			reverse_bits((uint32_t *)&color);
			our_mlx_put_pixel(game->image, x, y, color);
			y++;
		}
		if (game->rays[x].was_hit_vertical)
			texture_offset_x = (int)game->rays[x].wall_hit_y % TILE_SIZE;
		else
			texture_offset_x = (int)game->rays[x].wall_hit_x % TILE_SIZE;
		select_texture(&game->rays[x], game);
		texture_height = game->north_texture->height;
		while (y < wall_bottom_pixel)
		{
			distance_from_top = y + (wall_strip_height / 2) - (WINDOW_HEIGHT / 2);
			texture_offset_y = distance_from_top * ((float)texture_height / wall_strip_height);
			game->rays[x].current_texture_image = return_texture_image(&game->rays[x]);
			texel_color = put_pixel_color(game->rays[x].current_texture_image, texture_offset_x, texture_offset_y);
			reverse_bits(&texel_color);
			our_mlx_put_pixel(game->image, x, y, texel_color);
			y++;
		}
		while (y < WINDOW_HEIGHT)
		{
			floor_color = get_rgba(136, 66, 136, 255);
			reverse_bits((uint32_t *)&floor_color);
			our_mlx_put_pixel(game->image, x, y, floor_color);
			y++;
		}
		x++;
	}
} */