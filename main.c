/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:55:00 by asuc              #+#    #+#             */
/*   Updated: 2023/12/13 01:27:31 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <complex.h>
#include <stdio.h>

#define KEY_ESC 41
#define HEIGHT 1920
#define WIDTH 1080

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

void	free_all(t_data *data)
{
	free(data->tab);
}

int	hook_key(int keycode, void *data)
{
	if (keycode == KEY_ESC)
	{
		free_all(data);
		close_window(data);
	}
	ft_printf("keycode = %d\n", keycode);
	return (0);
}

double	map(double x, double in_min, double in_max, double out_min,
		double out_max)
{
	return (((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min));
}

double	map_color(double i, double max)
{
	return (i * 255 / max);
}

unsigned int	get_color(t_data *data)
{
	unsigned int	res;
	unsigned int	tmp;

	res = 0xFF58BA18;
	tmp = map_color(data->iter, data->max_iter);
	res += tmp << 16;
	res += tmp << 8;
	res += tmp;
	return (res);
}

int	mandelbrot(t_data *data)
{
	int		i;
	int		j;
	double	i0;
	double	j0;
	double	zr;
	double	zi;
	double	ktemp;
	double	ratio;
	double	log_zn;
	double	nu;

	i = 0;
	j = 0;
	if (WIDTH > HEIGHT)
		ratio = (double)WIDTH / (double)HEIGHT;
	else
		ratio = (double)HEIGHT / (double)WIDTH;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (WIDTH > HEIGHT)
			{
				i0 = map(i, 0, HEIGHT, -2, 2);
				j0 = map(j, 0, WIDTH, -2 * ratio, 2 * ratio);
			}
			else
			{
				i0 = map(i, 0, HEIGHT, -2 * ratio, 2 * ratio);
				j0 = map(j, 0, WIDTH, -2, 2);
			}
			zr = 0;
			zi = 0;
			data->max_iter = 100;
			data->iter = 0;
			while (zr * zr + zi * zi <= (1 << 16)
				&& data->iter < data->max_iter)
			{
				ktemp = zr * zr - zi * zi + i0;
				zi = 2 * zr * zi + j0;
				zr = ktemp;
				data->iter++;
			}
			if (data->iter == data->max_iter)
			{
				log_zn = log(zr * zr + zi * zi) / 2;
				nu = log(log_zn / log(2)) / log(2);
				data->iter = data->iter + 1 - (unsigned int)nu;
				data->color = powf((float)((i / data->max_iter) * 360, 1.5)
						% 360, 100), (float)(i / data->max_iter) * 100;
				mlx_pixel_put(data->mlx, data->win, i, j, data->color);
			}
			else
			{
				data->color = get_color(data);
				mlx_pixel_put(data->mlx, data->win, i, j, 0xFFFFFF);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	complex_calcul(t_data *data)
{
	(void)data;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	data->tab = malloc(sizeof(int) * 10);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, HEIGHT, WIDTH, "Fractol");
	data->img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	mlx_on_event(data->mlx, data->win, 0, hook_key, data);
	mandelbrot(data);
	mlx_loop(data->mlx);
	return (0);
}
