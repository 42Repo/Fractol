/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:39:14 by asuc              #+#    #+#             */
/*   Updated: 2024/01/17 00:03:50 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

size_t	max_value(size_t nb1, size_t nb2)
{
	if (nb1 > nb2)
		return (nb1);
	return (nb2);
}

static int	is_valid_number(const char *str)
{
	int	decimal_point;

	decimal_point = 0;
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str == '.')
		{
			if (decimal_point)
				return (0);
			decimal_point = 1;
		}
		else if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	check_input_julia(int argc, char **argv)
{
	if (argc == 4)
	{
		if (ft_strncmp(argv[1], "julia", max_value((size_t)(argv[1]), 5)) == 0)
		{
			if (is_valid_number(argv[2]) && is_valid_number(argv[3]))
				return (0);
		}
	}
	return (-1);
}

static double	ft_pow(double nb, double power)
{
	double	res;

	res = 1;
	while (power > 0)
	{
		res *= nb;
		power--;
	}
	return (res);
}

double	ft_atod(const char *str)
{
	double	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	if (str[i] == '.')
		res += ft_atod(&str[i + 1]) / ft_pow(10, ft_strlen(&str[i + 1]));
	return (res * sign);
}
