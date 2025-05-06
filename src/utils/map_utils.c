/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:06:03 by llage             #+#    #+#             */
/*   Updated: 2025/05/06 00:06:03 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	get_width(char **map)
{
	int	width;

	width = 0;
	while (map[0][width])
		width++;
	return (width);
}

int	get_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

char	**copy_map(char **map)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc(get_height(map) + 1, sizeof(char *));
	if (new_map == NULL)
		fatal_error_with_map("Unable to allocate memory for map", map);
	i = 0;
	while (map[i])
	{
		new_map[i] = ft_calloc(ft_strlen(map[i]) + 1, sizeof(char));
		if (new_map[i] == NULL)
			fatal_error_with_map("Unable to allocate memory for map line", map);
		ft_strncpy(new_map[i], map[i], ft_strlen(map[i]));
		i++;
	}
	return (new_map);
}

t_vector_2i	get_player(char **map)
{
	t_vector_2i	player;
	int			y;
	int			x;

	player.x = -1;
	player.y = -1;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				player.x = x;
				player.y = y;
				break ;
			}
			x++;
		}
		y++;
	}
	return (player);
}
