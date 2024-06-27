/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_2_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:54:34 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/27 11:55:26 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_texture_vertical(t_ray *ray, t_game *game, float angle)
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

void	select_texture_horizontal(t_ray *ray, t_game *game, float angle)
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

void	select_texture(t_ray *ray, t_game *game)
{
	float	angle;

	angle = ray->ray_angle;
	normalize_angle(&angle);
	if (ray->was_hit_vertical)
		select_texture_vertical(ray, game, angle);
	else
		select_texture_horizontal(ray, game, angle);
}

mlx_image_t	*return_texture_image(t_ray *ray)
{
	return (ray->current_texture_image);
}
