/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:55:00 by asuc              #+#    #+#             */
/*   Updated: 2023/12/16 21:21:53 by asuc             ###   ########.fr       */
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
	{
		mlx_destroy_display(data->mlx);
	}
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

int	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fractol [julia | mandelbrot | \
burningship]\n", 2);
		return (-1);
	}
	if (ft_strncmp(argv[1], "julia", 5) == 0)
		return (0);
	else if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		return (1);
	else if (ft_strncmp(argv[1], "burningship", 11) == 0)
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
	data->mode = check_args(argc, argv);
	if (data->mode == -1)
	{
		free(data);
		return (0);
	}
	init_palette(palette);
	data->palette = palette;
	init_data(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fract-ol");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_on_event(data->mlx, data->win, 0, hook_key_keyboard, data);
	mlx_on_event(data->mlx, data->win, 5, hook_key_keyboard, data);
	mlx_on_event(data->mlx, data->win, 4, hook_key_mouse, data);
	choose_fractal(data);
	mlx_loop(data->mlx);
	return (0);
}
