/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:26:58 by llage             #+#    #+#             */
/*   Updated: 2025/05/02 19:03:33 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <libft.h>
# include <ft_printf.h>
# include <mlx.h>
# include <SDL_scancode.h>

typedef struct s_context
{
	mlx_context				context;
	mlx_window_create_info	window_info;
	mlx_window				window;
}	t_context;

void	window_hook(int event, void* param);
void	key_down_hook(int key, void* param);
void	loop_hook(void* param);

#endif
