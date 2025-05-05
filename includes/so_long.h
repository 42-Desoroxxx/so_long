/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:26:58 by llage             #+#    #+#             */
/*   Updated: 2025/05/05 19:57:49 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <libft.h>
# include <ft_printf.h>
# include <get_next_line.h>
# include <mlx.h>
# include <SDL_scancode.h>
# include <fcntl.h>

typedef struct s_context
{
	mlx_context				context;
	mlx_window_create_info	window_info;
	mlx_window				window;
}	t_context;

typedef struct s_vector_2i
{
	int x;
	int y;
}	t_vector_2i;


// Utils

_Noreturn void	fatal_error(char *message);
_Noreturn void	fatal_error_with_map(char *message, char **map);
int				open_map(char *path);
void 			free_map(char **map);
char			**copy_map(char **map);
char			**validate_via_flood(char **map);
t_vector_2i		get_player(char **map);

// Parsing

void			parse_map(int fd);
void			check_map(char **map);

// Hooks

void			window_hook(int event, void* param);
void			key_down_hook(int key, void* param);
void			loop_hook(void* param);

#endif
