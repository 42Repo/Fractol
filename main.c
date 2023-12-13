/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:55:00 by asuc              #+#    #+#             */
/*   Updated: 2023/12/13 07:06:34 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <complex.h>
#include <stdio.h>
#include <time.h>

#define KEY_ESC 41
#define HEIGHT 800
#define WIDTH 800
#define PALETTE_SIZE 512

int				mandelbrot(t_data *data);

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
	(void)data;
}

double	map(double x, double in_min, double in_max, double out_min,
		double out_max)
{
	return (((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min));
}

void	apply_zoom(t_data *data)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;

	mlx_mouse_get_pos(data->mlx, &data->mouse_x, &data->mouse_y);
	zoom_factor = 1.1;
	mouse_re = map(data->mouse_x, 0, WIDTH, data->center_x - 2
			/ data->zoom_factor, data->center_x + 2 / data->zoom_factor);
	mouse_im = map(data->mouse_y, 0, HEIGHT, data->center_y - 2
			/ data->zoom_factor, data->center_y + 2 / data->zoom_factor);
	data->zoom_factor *= zoom_factor;
	data->center_x = mouse_re + (data->center_x - mouse_re) / zoom_factor;
	data->center_y = mouse_im + (data->center_y - mouse_im) / zoom_factor;
}

void	apply_dezoom(t_data *data)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;

	mlx_mouse_get_pos(data->mlx, &data->mouse_x, &data->mouse_y);
	zoom_factor = 0.9;
	mouse_re = map(data->mouse_x, 0, WIDTH, data->center_x - 2
			/ data->zoom_factor, data->center_x + 2 / data->zoom_factor);
	mouse_im = map(data->mouse_y, 0, HEIGHT, data->center_y - 2
			/ data->zoom_factor, data->center_y + 2 / data->zoom_factor);
	data->zoom_factor *= zoom_factor;
	data->center_x = mouse_re + (data->center_x - mouse_re) / zoom_factor;
	data->center_y = mouse_im + (data->center_y - mouse_im) / zoom_factor;
}

void	increase_max_iter(t_data *data)
{
	data->max_iter += 10;
}
void	decrease_max_iter(t_data *data)
{
	data->max_iter -= 10;
}

void	set_iteration_to(t_data *data, int iter)
{
	data->max_iter = iter;
}

int	hook_key(int keycode, void *data)
{
	if (keycode == KEY_ESC || keycode == 0)
	{
		free_all(data);
		close_window(data);
	}
	if (keycode == 1)
		apply_zoom(data);
	if (keycode == 2)
		apply_dezoom(data);
	if (keycode == 87)
		increase_max_iter(data);
	if (keycode == 86)
		decrease_max_iter(data);
	if (keycode == 96)
		set_iteration_to(data, 1000);
	if (keycode == 95)
		set_iteration_to(data, 100);
	if (keycode == 1 || keycode == 2 || keycode == 87 || keycode == 86 || keycode == 96 || keycode == 95)
		mandelbrot(data);

	ft_printf("keycode = %d\n", keycode);
	return (0);
}

unsigned int	linear_interpolate(unsigned int color1, unsigned int color2,
		double t)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)((1 - t) * ((color1 >> 16) & 0xFF) + t
			* ((color2 >> 16) & 0xFF));
	g = (unsigned int)((1 - t) * ((color1 >> 8) & 0xFF) + t
			* ((color2 >> 8) & 0xFF));
	b = (unsigned int)((1 - t) * (color1 & 0xFF) + t * (color2 & 0xFF));
	return ((r << 16) | (g << 8) | b);
}

unsigned int	get_palette_color(int index, unsigned int palette[])
{
	return (palette[index % PALETTE_SIZE]);
}

int	mandelbrot(t_data *data)
{
	int				i;
	int				j;
	double			i0;
	double			j0;
	double			zr;
	double			zi;
	double			ktemp;
	double			ratio;
	double			log_zn;
	double			nu;
	unsigned int	color1;
	unsigned int	color2;

	data->min_x = data->center_x - (2.0 / data->zoom_factor);
	data->max_x = data->center_x + (2.0 / data->zoom_factor);
	data->min_y = data->center_y - (2.0 / data->zoom_factor);
	data->max_y = data->center_y + (2.0 / data->zoom_factor);
	i = 0;
	j = 0;
	if (WIDTH > HEIGHT)
		ratio = (double)HEIGHT / (double)WIDTH;
	else
		ratio = (double)WIDTH / (double)HEIGHT;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			if (WIDTH > HEIGHT)
			{
				i0 = map(i, 0, WIDTH, data->min_x, data->max_x);
				j0 = map(j, 0, HEIGHT, data->min_y * ratio, data->max_y
						* ratio);
			}
			else
			{
				i0 = map(i, 0, WIDTH, data->min_x * ratio, data->max_x * ratio);
				j0 = map(j, 0, HEIGHT, data->min_y, data->max_y);
			}
			zr = 0;
			zi = 0;
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
			}
			color1 = get_palette_color(floor(data->iter), data->palette);
			color2 = get_palette_color(floor(data->iter) + 1, data->palette);
			data->color = linear_interpolate(color1, color2, data->iter
					- floor(data->iter));
			mlx_pixel_put(data->mlx, data->win, i, j, data->color);
			j++;
		}
		i++;
	}
	return (0);
}

void	init_palette(unsigned int palette[])
{
	int				i;
	double			t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	i = 0;
	while (i < PALETTE_SIZE)
	{
		t = (double)i / (PALETTE_SIZE - 1);
		r = (unsigned int)(9 * (1 - t) * t * t * t * 255);
		g = (unsigned int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (unsigned int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		palette[i] = (r << 16) | (g << 8) | b;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data			*data;
	unsigned int	palette[PALETTE_SIZE];

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	init_palette(palette);
	data->center_x = 0;
	data->center_y = 0;
	data->zoom_factor = 1;
	data->max_iter = 50;
	data->palette = palette;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fractol");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_on_event(data->mlx, data->win, 0, hook_key, data);
	mlx_on_event(data->mlx, data->win, 4, hook_key, data);
	mlx_on_event(data->mlx, data->win, 5, hook_key, data);
	mandelbrot(data);
	mlx_loop(data->mlx);
	return (0);
}
