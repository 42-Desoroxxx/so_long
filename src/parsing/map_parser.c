/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:22:14 by llage             #+#    #+#             */
/*   Updated: 2025/05/05 19:22:17 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static char	**add_to_map(char **map, char *line)
{
	char	**new_map;
	int		current_map_length;

	current_map_length = 0;
	while (map[current_map_length])
		current_map_length++;
	new_map = ft_calloc(current_map_length + 2, sizeof(char *));
	if (new_map == NULL)
		fatal_error_with_map("Unable to allocate memory for map", map);
	ft_memcpy(new_map, map, (current_map_length) * sizeof(char *));
	new_map[current_map_length] = ft_calloc(ft_strlen(line), sizeof(char));
	if (new_map[current_map_length] == NULL)
	{
		free(new_map);
		fatal_error_with_map("Unable to allocate memory for map line", map);
	}
	if (line[ft_strlen(line) - 1] == '\n')
		ft_strlcpy(new_map[current_map_length], line, ft_strlen(line));
	else
		ft_strlcpy(new_map[current_map_length], line, ft_strlen(line) + 1);
	new_map[current_map_length + 1] = NULL;
	return (new_map);
}

static char	**read_map(const int fd)
{
	char	**new_map;
	char	**map;
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		fatal_error("Unable to read map file (Is it empty?)");
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	map = ft_calloc(1, sizeof(char *));
	if (map == NULL)
		fatal_error("Unable to allocate memory for map");
	map[0] = NULL;
	while (line && line[0] != '\n')
	{
		new_map = add_to_map(map, line);
		free(map);
		free(line);
		map = new_map;
		line = get_next_line(fd);
	}
	return (map);
}

void	parse_map(const int fd)
{
	char	**map;

	map = read_map(fd);
	check_map(map);

	ft_printf("Read Map:\n");
	for (size_t i = 0; i < ft_strlen((char *)map); i++)
		ft_printf("%d:%s\n", i, map[i]);
}
