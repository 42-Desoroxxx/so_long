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

void	create_window(t_context *context)
{
	context->window_info.title = "so_long";
	context->window_info.width = 1280;
	context->window_info.height = 720;
	context->window = mlx_new_window(context->context, &context->window_info);
	if (context->window == NULL)
		exit(EXIT_FAILURE);
}

void	create_textures(t_context *context)
{
	context->texture_player = mlx_new_image_from_file(context->context,
			"textures/player.png", 0, 0);
	context->texture_collectible = mlx_new_image_from_file(context->context,
			"textures/collectible.png", 0, 0);
	context->texture_wall = mlx_new_image_from_file(context->context,
			"textures/wall.png", 0, 0);
	context->texture_exit_closed = mlx_new_image_from_file(context->context,
			"textures/exit_closed.png", 0, 0);
	context->texture_exit_open = mlx_new_image_from_file(context->context,
			"textures/exit_open.png", 0, 0);
}

void	cleanup(t_context context)
{
	mlx_destroy_image(context.context, context.texture_player);
	mlx_destroy_image(context.context, context.texture_collectible);
	mlx_destroy_image(context.context, context.texture_wall);
	mlx_destroy_image(context.context, context.texture_exit_closed);
	mlx_destroy_image(context.context, context.texture_exit_open);
	mlx_destroy_window(context.context, context.window);
	mlx_destroy_context(context.context);
}

int	main(int argc, char *argv[])
{
	t_context	context;

	if (argc != 2)
		fatal_error("Must provide a path to a map file");
	ft_bzero(&context, sizeof(context));
	parse_map(open_map(argv[1]), &context);
	context.context = mlx_init();
	if (context.context == NULL)
	{
		free_map(context.map);
		exit(EXIT_FAILURE);
	}
	create_textures(&context);
	create_window(&context);
	mlx_on_event(context.context, context.window, MLX_WINDOW_EVENT,
		window_hook, &context);
	mlx_on_event(context.context, context.window, MLX_KEYDOWN,
		key_down_hook, &context);
	mlx_set_fps_goal(context.context, 24);
	context.player = get_player(context.map);
	mlx_add_loop_hook(context.context, loop_hook, &context);
	mlx_loop(context.context);
	free_map(context.map);
	cleanup(context);
}
