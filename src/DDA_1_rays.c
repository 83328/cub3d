/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_1_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:10:49 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/27 11:13:10 by alimpens         ###   ########.fr       */
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
