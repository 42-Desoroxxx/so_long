#ifndef SO_LONG_H
# define SO_LONG_H

# include <libft.h>
# include <ft_printf.h>
# include <mlx.h>

typedef struct s_context
{
	mlx_context				context;
	mlx_window_create_info	window_info;
	mlx_window				window;
}	t_context;

#endif
