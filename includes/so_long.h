/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:26:58 by llage             #+#    #+#             */
/*   Updated: 2025/05/06 04:26:40 by llage            ###   ########.fr       */
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

typedef struct s_vector_2i
{
	int	x;
	int	y;
}	t_vector_2i;

typedef struct s_context
{
	mlx_context				context;
	mlx_window_create_info	window_info;
	mlx_window				window;
	t_vector_2i				player;
	int						moves;
	int						collectible_left;
	void					*texture_player;
	void					*texture_collectible;
	void					*texture_wall;
	void					*texture_exit_closed;
	void					*texture_exit_open;
	char					**map;
}	t_context;

// Utils

_Noreturn void	fatal_error(char *message);
_Noreturn void	fatal_error_with_map(char *message, char **map);
_Noreturn void	fatal_error_with_fd(char *message, int fd);
int				open_map(char *path);
void			free_map(char **map);
int				get_width(char **map);
int				get_height(char **map);
char			**copy_map(char **map);
void			validate_via_flood(char **map);
t_vector_2i		get_player(char **map);

// Parsing

void			parse_map(int fd, t_context *context);
int				check_map(char **map);

// Hooks

void			window_hook(int event, void *param);
void			key_down_hook(int key, void *param);
void			loop_hook(void *param);

#endif
