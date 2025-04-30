/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llage <desoroxxx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 05:33:55 by llage             #+#    #+#             */
/*   Updated: 2024/10/20 09:55:33 by llage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>

long	ft_atol(const char *str)
{
	long long	result;
	int			sign;

	str = skip_whitespace(str);
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	result = 0;
	while (ft_isdigit(*str))
	{
		if ((sign == 1 && (result > (LONG_MAX - (*str - '0')) / 10))
			|| (sign == -1 && (-result < (LONG_MIN + (*str - '0')) / 10)))
		{
			if (sign == 1)
				return (LONG_MAX);
			return (LONG_MIN);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
