/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:54:27 by llage             #+#    #+#             */
/*   Updated: 2025/05/05 21:32:17 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	is_valid_extension(char *path)
{
	const char	*extension = ft_strrchr(path, '.');

	if (extension == NULL)
		fatal_error("Missing file extension, must be .ber");
	if (ft_strncmp(extension, ".ber", 4) != 0)
		fatal_error("Invalid file extension, must be `.ber`");
}


int	open_map(char *path)
{
	int	fd;

	is_valid_extension(path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		fatal_error("Unable to open map file (Are the permissions correct?) "
			"(Does it exist?)");
	return (fd);
}
