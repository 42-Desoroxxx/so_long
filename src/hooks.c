/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 08:29:15 by llage             #+#    #+#             */
/*   Updated: 2025/05/04 09:23:34 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end((mlx_context)param);
}

void	key_down_hook(int key, void *param)
{
	if (key == SDL_SCANCODE_ESCAPE)
		mlx_loop_end((mlx_context)param);
	else if (key == SDL_SCANCODE_W)
		ft_printf("W\n");
	else if (key == SDL_SCANCODE_A)
		ft_printf("A\n");
	else if (key == SDL_SCANCODE_S)
		ft_printf("S\n");
	else if (key == SDL_SCANCODE_D)
		ft_printf("D\n");
}

void	loop_hook(void *param)
{
	const t_context	*context = (t_context*)param;

	mlx_clear_window(context->context, context->window,
		(mlx_color){.rgba = 0x000000FF});
}
