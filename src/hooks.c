/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 08:29:15 by llage             #+#    #+#             */
/*   Updated: 2025/05/06 17:04:23 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end((mlx_context)param);
}

void	move_player(t_context context, int x, int y)
{
	if (context.map[y][x] == '1')
		return ;
	context.player.x = x;
	context.player.y = y;
	context.moves++;
	printf("Moves: %d\n", context.moves);
	if (context.map[y][x] == 'C')
	{
		context.collectible_left--;
		context.map[y][x] = '0';
	}
	else if (context.map[y][x] == 'E' && context.collectible_left == 0)
	{
		ft_printf("You win!\n");
		mlx_loop_end(context.context);
	}
}

void	key_down_hook(int key, void *param)
{
	const t_context	*context = (t_context*)param;

	if (key == SDL_SCANCODE_ESCAPE)
		mlx_loop_end((mlx_context)param);
	else if (key == SDL_SCANCODE_W)
		move_player(*context, context->player.x, context->player.y - 1);
	else if (key == SDL_SCANCODE_A)
		move_player(*context, context->player.x - 1, context->player.y);
	else if (key == SDL_SCANCODE_S)
		move_player(*context, context->player.x, context->player.y + 1);
	else if (key == SDL_SCANCODE_D)
		move_player(*context, context->player.x + 1, context->player.y);
}

static void	draw_tile(t_context context, int y, int x)
{
	if (y == context.player.y && x == context.player.x)
		mlx_put_image_to_window(context.context, context.window,
			context.texture_player, x * 32, y * 32);
	else if (context.map[y][x] == 'C')
		mlx_put_image_to_window(context.context, context.window,
			context.texture_collectible, x * 32, y * 32);
	else if (context.map[y][x] == 'E' && context.collectible_left > 0)
		mlx_put_image_to_window(context.context, context.window,
			context.texture_exit_closed, x * 32, y * 32);
	else if (context.map[y][x] == 'E' && context.collectible_left == 0)
		mlx_put_image_to_window(context.context, context.window,
			context.texture_exit_open, x * 32, y * 32);
	else if (context.map[y][x] == '1')
		mlx_put_image_to_window(context.context, context.window,
			context.texture_wall, x * 32, y * 32);
}

void	loop_hook(void *param)
{
	const t_context	*context = (t_context*)param;
	int				y;
	int				x;

	y = 0;
	while (y < get_height(context->map))
	{
		x = 0;
		while (x < get_width(context->map))
		{
			draw_tile(*context, y, x);
			x++;
		}
		y++;
	}
	mlx_clear_window(context->context, context->window,
		(mlx_color){.rgba = 0x000000FF});
}
