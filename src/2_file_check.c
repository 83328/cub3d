/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_file_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:30:36 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/23 15:30:01 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file(int argc, char **argv)
{
	int	i;

	if (argc < 2 || argc > 3)
		ft_error(ERR_ARGS, NULL);
	i = ft_strlen(argv[1]);
	if (ft_strnstr(&argv[1][i - 4], ".cub", 4) == NULL)
		ft_error(ERR_FILETYPE, NULL);
}
