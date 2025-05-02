/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <llage@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:38:46 by llage             #+#    #+#             */
/*   Updated: 2025/04/30 19:21:39 by llage            ###   ########.fr       */
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

int	main(void)
{
	t_context	context;

	context.context = mlx_init();
	if (context.context == NULL)
		exit(EXIT_FAILURE);
	create_window(context);
	mlx_loop(context.context);
}
