/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:59:27 by llage             #+#    #+#             */
/*   Updated: 2025/05/06 04:44:26 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static int	count_char(const char c, char **map)
{
	static int	collectible;
	static bool	has_player;
	static bool	has_exit;

	if (c == 'C')
		collectible++;
	else if (c == 'P')
	{
		if (has_player)
			fatal_error_with_map("Map contains multiple players", map);
		has_player = true;
	}
	else if (c == 'E')
	{
		if (has_exit)
			fatal_error_with_map("Map contains multiple exits", map);
		has_exit = true;
	}
	if (c == 'F' && !has_player)
		fatal_error_with_map("Map does not contain a player", map);
	if (c == 'F' && !has_exit)
		fatal_error_with_map("Map does not contain an exit", map);
	return (collectible);
}

static void	validate_chars(char **map)
{
	int		collectible;
	char	c;
	int		i;
	int		j;

	collectible = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			c = map[i][j];
			if (c != '0' && c != '1' && c != 'C' && c != 'P' && c != 'E')
				fatal_error_with_map("Invalid character in map", map);
			collectible = count_char(c, map);
			j++;
		}
		i++;
	}
	count_char('F', map);
	if (collectible < 1)
		fatal_error_with_map("Map does not contain enough collectibles", map);
}

static void	validate_rectangle(char **map)
{
	const size_t	length = ft_strlen(map[0]);
	int				i;
	int				j;

	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) != length)
			fatal_error_with_map("Map is not a rectangle", map);
		j = 0;
		if (i == 0 || map[i + 1] == NULL)
		{
			while (map[i][j])
			{
				if (map[i][j] != '1')
					fatal_error_with_map("Map outer layer is not fully walls",
						map);
				j++;
			}
		}
		else if (map[i][get_width(map) - 1] != '1' || map[i][0] != '1')
			fatal_error_with_map("Map outer layer is not fully walls", map);
		i++;
	}
}

void	check_map(char **map)
{
	validate_chars(map);
	validate_rectangle(map);
	validate_via_flood(map);
}
