/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:59:53 by llage             #+#    #+#             */
/*   Updated: 2025/05/05 19:38:04 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

_Noreturn void	fatal_error_with_fd(char *message, int fd)
{
	close(fd);
	ft_fprintf(STDERR_FILENO, "Error\n%s\n", message);
	exit(EXIT_FAILURE);
}

_Noreturn void	fatal_error_with_map(char *message, char **map)
{
	free_map(map);
	ft_fprintf(STDERR_FILENO, "Error\n%s\n", message);
	exit(EXIT_FAILURE);
}

_Noreturn void	fatal_error(char *message)
{
	ft_fprintf(STDERR_FILENO, "Error\n%s\n", message);
	exit(EXIT_FAILURE);
}
