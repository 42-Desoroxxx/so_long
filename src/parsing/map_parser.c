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

static char	**add_to_map(char **map, char *line, int fd)
{
	const int	current_map_length = get_height(map);
	char		**new_map;
	char		*new_line;

	new_map = ft_calloc(current_map_length + 2, sizeof(char *));
	if (new_map == NULL)
	{
		close(fd);
		fatal_error_with_map("Unable to allocate memory for map", map);
	}
	ft_memcpy(new_map, map, (current_map_length) * sizeof(char *));
	new_line = ft_strtrim(line, "\n\r");
	new_map[current_map_length] = ft_calloc(ft_strlen(new_line) + 1,
			sizeof(char));
	if (new_map[current_map_length] == NULL)
	{
		close(fd);
		free(new_map);
		free(new_line);
		fatal_error_with_map("Unable to allocate memory for map line", map);
	}
	ft_strncpy(new_map[current_map_length], new_line, ft_strlen(new_line));
	free(new_line);
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
		fatal_error_with_fd("Unable to read map file (Is it empty?)", fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	map = ft_calloc(1, sizeof(char *));
	if (map == NULL)
		fatal_error_with_fd("Unable to allocate memory for map", fd);
	map[0] = NULL;
	while (line && line[0] != '\n')
	{
		new_map = add_to_map(map, line, fd);
		free(map);
		free(line);
		map = new_map;
		line = get_next_line(fd);
	}
	return (map);
}

void	parse_map(const int fd, t_context context)
{
	char	**map;

	map = read_map(fd);
	close(fd);
	context.collectible_left = check_map(map);
	context.map = map;
}
