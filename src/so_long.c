/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:38:46 by llage             #+#    #+#             */
/*   Updated: 2025/05/06 06:46:48 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	create_window(t_context context)
{
	context.window_info.title = "so_long";
	context.window_info.width = 1280;
	context.window_info.height = 720;
	context.window = mlx_new_window(context.context, &context.window_info);
	if (context.window == NULL)
		exit(EXIT_FAILURE);
}

void	cleanup(t_context context)
{
	mlx_destroy_window(context.context, context.window);
	mlx_destroy_context(context.context);
}

int	main(int argc, char *argv[])
{
	t_context	context;
	char		**map;

	if (argc != 2)
		fatal_error("Must provide a path to a map file");
	map = parse_map(open_map(argv[1]));
	ft_bzero(&context, sizeof(context));
	context.context = mlx_init();
	if (context.context == NULL)
	{
		free_map(map);
		exit(EXIT_FAILURE);
	}
	mlx_on_event(context.context, context.window, MLX_WINDOW_EVENT, window_hook,
		context.context);
	mlx_on_event(context.context, context.window, MLX_KEYDOWN, key_down_hook,
		context.context);
	mlx_set_fps_goal(context.context,24);
	create_window(context);
	mlx_add_loop_hook(context.context, loop_hook, &context);
	mlx_loop(context.context);
	free_map(map);
	cleanup(context);
}
