/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:55:00 by asuc              #+#    #+#             */
/*   Updated: 2024/01/15 00:21:05 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	close_window(t_data *data)
{
	mlx_loop_end(data->mlx);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data);
	exit(0);
}

void	init_data(t_data *data)
{
	data->center_x = 0;
	data->center_y = 0;
	data->zoom_factor = 1;
	data->max_iter = 50;
	data->c_i = 0.158;
	data->c_r = -0.8;
	data->color_mode = 0;
	data->smooth = 0;
	data->pixel_size = 1;
}


double	ft_atod(const char *str)
{
	double	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
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
		res += ft_atod(&str[i + 1]) / pow(10, ft_strlen(&str[i + 1]));
	return (res * sign);
}

int	set_julia(char **argv, t_data *data)
{
	data->c_i = (double)ft_atod(argv[2]);
	data->c_r = (double)ft_atod(argv[3]);
	return (0);
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

int	check_args(int argc, char **argv, t_data *data)
{
	if (argc != 2 && check_input_julia(argc, argv) != 0)
	{
		ft_putstr_fd("Usage: ./fractol [julia | mandelbrot | \
burningship]\n", 2);
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
	{
		ft_putstr_fd("Usage: ./fractol [julia | mandelbrot | \
burningship]\n", 2);
		return (-1);
	}
}

int	main(int argc, char **argv)
{
	t_data			*data;
	unsigned int	palette[PALETTE_SIZE];

	(void)argc;
	data = malloc(sizeof(t_data));
	init_data(data);
	data->mode = check_args(argc, argv, data);
	if (data->mode == -1)
	{
		free(data);
		return (0);
	}
	init_palette(palette);
	data->palette = palette;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fractol");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_on_event(data->mlx, data->win, 0, hook_key_keyboard, data);
	mlx_on_event(data->mlx, data->win, 5, hook_key_keyboard, data);
	mlx_on_event(data->mlx, data->win, 4, hook_key_mouse, data);
	choose_fractal(data);
	mlx_loop(data->mlx);
	return (0);
}
