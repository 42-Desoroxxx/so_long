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

int	main(void)
{
	const mlx_context		mlx = mlx_init();
	mlx_window_create_info	info = { 0 };
	mlx_window				window;

	ft_printf("Hello World!\n");
	info.title = "so_long";
	info.width = 1280;
	info.height = 720;
	window = mlx_new_window(mlx, &info);
	(void)window;
	mlx_loop(mlx);
}
