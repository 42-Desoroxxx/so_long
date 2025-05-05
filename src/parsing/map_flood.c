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

static char	**flood_fill(char **map, int x, int y, int height, int width)
{
	char			**flooded_map;
	int changes;

	flooded_map = copy_map(map);
	if (flooded_map == NULL)
		fatal_error_with_map("Unable to allocate memory for flooded map", map);
	while (true)
	{
		changes = 0;
		y = 0;
		while (y < height) {
			x = 0;
			while (x < width) {
				if (flooded_map[y][x] == 'P') {
					if (y > 0 && (flooded_map[y-1][x] == '0' || flooded_map[y-1][x] == 'C' || flooded_map[y-1][x] == 'E')) {
						flooded_map[y-1][x] = 'P';
						changes++;
					}
					if (x < width-1 && (flooded_map[y][x+1] == '0' || flooded_map[y][x+1] == 'C' || flooded_map[y][x+1] == 'E')) {
						flooded_map[y][x+1] = 'P';
						changes++;
					}
					if (y < height-1 && (flooded_map[y+1][x] == '0' || flooded_map[y+1][x] == 'C' || flooded_map[y+1][x] == 'E')) {
						flooded_map[y+1][x] = 'P';
						changes++;
					}
					if (x > 0 && (flooded_map[y][x-1] == '0' || flooded_map[y][x-1] == 'C' || flooded_map[y][x-1] == 'E')) {
						flooded_map[y][x-1] = 'P';
						changes++;
					}
				}
				x++;
			}
			y++;
		}
		if (changes == 0)
			break;
	}
	return (flooded_map);
}

char	**validate_via_flood(char **map)
{
	const t_vector_2i	player = get_player(map);
	char				**flooded_map;

	if (player.x == -1 || player.y == -1)
		fatal_error_with_map("Map does not contain a player", map);
	flooded_map = flood_fill(map, player.x, player.y,
		(int) ft_strlen((char *) map) - 1,
		(int) ft_strlen((char *) map[0]));
	return (flooded_map);
}