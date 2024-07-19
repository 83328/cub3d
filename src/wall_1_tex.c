/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_1_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:47:04 by alimpens          #+#    #+#             */
/*   Updated: 2024/07/19 13:57:50 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_copy_path(char *path, char *file_path)
{
	int len = ft_strlen(file_path);
	ft_strlcpy(path, file_path, len);
	path[len] = '\0';
}

void	load_test_texture_north(t_game *game)
{
	char path[100];
	ft_copy_path(path, game->file_path_no);
	game->north_texture = mlx_load_png(path);
	if (game->north_texture == NULL)
		ft_error(ERR_TEX, NULL);
	game->image_north_texture = 
		mlx_texture_to_image(game->mlx, game->north_texture);
}

void	load_test_texture_south(t_game *game)
{
	char path[100];
	ft_copy_path(path, game->file_path_so);
	game->south_texture = mlx_load_png(path);
	if (game->south_texture == NULL)
		ft_error(ERR_TEX, NULL);
	game->image_south_texture = 
		mlx_texture_to_image(game->mlx, game->south_texture);
}

void	load_test_texture_west(t_game *game)
{
	char path[100];
	ft_copy_path(path, game->file_path_we);
	game->west_texture = mlx_load_png(path);
	if (game->west_texture == NULL)
		ft_error(ERR_TEX, NULL);
	game->image_west_texture = 
		mlx_texture_to_image(game->mlx, game->west_texture);
}

void	load_test_texture_east(t_game *game)
{
	char path[100];
	ft_copy_path(path, game->file_path_ea);
	game->east_texture = mlx_load_png(path);
	if (game->east_texture == NULL)
		ft_error(ERR_TEX, NULL);
	game->image_east_texture = 
		mlx_texture_to_image(game->mlx, game->east_texture);
}
