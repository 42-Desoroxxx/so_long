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

typedef struct s_ctx
{
	mlx_context				mlx;
	mlx_window_create_info	win_info;
	mlx_window				win;
}t_ctx;

int	main(void)
{
	t_ctx					ctx = { 0 };


	ctx.mlx = mlx_init();
	if (ctx.mlx == NULL)
		return (1);
	ctx.win_info.title = "so_long";
	ctx.win_info.width = 1280;
	ctx.win_info.height = 720;
	ctx.win = mlx_new_window(ctx.mlx, &ctx.win_info);
	if (ctx.win == NULL)
		return (1);
	mlx_loop(ctx.mlx);
	return (0);
}
