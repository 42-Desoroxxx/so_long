/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:16:19 by llage             #+#    #+#             */
/*   Updated: 2025/05/06 00:16:19 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	check_and_fill(char **map, int x, int y, int *changes)
{
	const int	direction_x[4] = {0, 1, 0, -1};
	const int	direction_y[4] = {-1, 0, 1, 0};
	int			new_x;
	int			new_y;
	int			i;

	i = 0;
	while (i < 4)
	{
		new_x = x + direction_x[i];
		new_y = y + direction_y[i];
		if (new_x >= 0 && new_x < get_width(map) && new_y >= 0
			&& new_y < get_height(map) && (map[new_y][new_x] == '0'
			|| map[new_y][new_x] == 'C' || map[new_y][new_x] == 'E'))
		{
			map[new_y][new_x] = 'P';
			(*changes)++;
		}
		i++;
	}
}

static char	**flood_fill(char **map, int x, int y)
{
	char	**flooded_map;
	int		changes;

	flooded_map = copy_map(map);
	if (flooded_map == NULL)
		fatal_error_with_map("Unable to allocate memory for flooded map", map);
	while (true)
	{
		changes = 0;
		y = 0;
		while (y < get_height(flooded_map))
		{
			x = 0;
			while (x < ((int) ft_strlen(flooded_map[0])))
			{
				if (flooded_map[y][x] == 'P')
					check_and_fill(flooded_map, x, y, &changes);
				x++;
			}
			y++;
		}
		if (changes == 0)
			break ;
	}
	return (flooded_map);
}

static void	validate_everything(char **map, char **flooded_map, int x, int y)
{
	while (y < get_height(flooded_map))
	{
		x = 0;
		while (x < get_width(flooded_map))
		{
			if (flooded_map[y][x] == 'P' && (y == 0 || y == get_height(map) - 1
				|| x == 0 || x == get_width(map) - 1))
			{
				free_map(flooded_map);
				fatal_error_with_map("Map is not closed", map);
			}
			if (map[y][x] == 'E' && flooded_map[y][x] != 'P')
			{
				free_map(flooded_map);
				fatal_error_with_map("Exit is not accessible", map);
			}
			if (map[y][x] == 'C' && flooded_map[y][x] != 'P')
			{
				free_map(flooded_map);
				fatal_error_with_map("A collectible is not accessible", map);
			}
			x++;
		}
		y++;
	}
}

void	validate_via_flood(char **map)
{
	const t_vector_2i	player = get_player(map);
	char				**flooded_map;

	flooded_map = flood_fill(map, player.x, player.y);
	validate_everything(map, flooded_map, 0, 0);
	free_map(flooded_map);
}
