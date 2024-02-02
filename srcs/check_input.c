/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:12:28 by asuc              #+#    #+#             */
/*   Updated: 2024/02/02 01:43:58 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static int	set_julia(char **argv, t_data *data)
{
	data->c_i = (double)ft_atod(argv[2]);
	data->c_r = (double)ft_atod(argv[3]);
	return (0);
}

static int	check_input(int argc, char **argv)
{
	if (argc == 4)
		if (ft_strncmp(argv[1], "julia", max_value((size_t)(argv[1]), 5)) == 0)
			return (0);
	if (argc == 2)
	{
		if (ft_strncmp(argv[1], "mandelbrot", max_value((size_t)(argv[1]),
				11)) == 0)
			return (0);
		if (ft_strncmp(argv[1], "burningship", max_value((size_t)(argv[1]),
				11)) == 0)
			return (0);
	}
	return (-1);
}

int	check_args(int argc, char **argv, t_data *data)
{
	if (check_input(argc, argv) == -1)
	{
		if (argv[1] != NULL && ft_strncmp(argv[1], "julia",
				max_value((size_t)(argv[1]), 5)) == 0)
			return (error("Usage: ./fractol julia [c_r] [c_i]\n"));
		else
			return (error("Usage: ./fractol [julia | mandelbrot |\
burningship]\n"));
	}
	if (argc == 4 && check_input_julia(argc, argv) == -1)
	{
		ft_putstr_fd("Usage: ./fractol julia [c_r] [c_i]\n", 2);
		return (-1);
	}
	if (ft_strncmp(argv[1], "julia", max_value((size_t)(argv[1]), 5)) == 0)
		return (set_julia(argv, data));
	else if (ft_strncmp(argv[1], "mandelbrot", max_value((size_t)(argv[1]),
			11)) == 0)
		return (1);
	else if (ft_strncmp(argv[1], "burningship", max_value((size_t)(argv[1]),
			11)) == 0)
		return (2);
	else
		return (error("Usage: ./fractol [julia | mandelbrot | burningship]\n"));
}
