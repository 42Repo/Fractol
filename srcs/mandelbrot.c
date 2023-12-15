/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:22:07 by asuc              #+#    #+#             */
/*   Updated: 2023/12/15 04:29:10 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

double	map(double x, double in_min, double in_max, double out_min,
		double out_max)
{
	return (((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min));
}

void	put_pixel_art(t_data *data, int x, int y, unsigned int color)
{
	int	dx;
	int	dy;

	dx = 0;
	while (dx < data->pixel_size)
	{
		dy = 0;
		while (dy < data->pixel_size)
		{
			if (x + dx < WIDTH && y + dy < HEIGHT)
			{
				mlx_pixel_put(data->mlx, data->win, x + dx, y + dy, color);
			}
			dy++;
		}
		dx++;
	}
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
	unsigned int	color1;
	unsigned int	color2;
	double			log_zn;
	double			nu;
	double			mu;

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
			while (zr * zr + zi * zi <= 4 && data->iter < data->max_iter)
			{
				ktemp = zr * zr - zi * zi + i0;
				zi = 2 * zr * zi + j0;
				zr = ktemp;
				data->iter++;
			}
			if (data->smooth == 1)
			{
				log_zn = log(zr * zr + zi * zi) / 2;
				nu = log(log_zn / log(2)) / log(2);
				mu = (double)data->iter + 1 - nu;
				color1 = get_palette_color(floor(mu), data->palette);
				color2 = get_palette_color(ceil(mu), data->palette);
				data->color = linear_interpolate(color1, color2, mu - floor(mu));
			}
			if (data->color_mode == 0)
			{
				data->color = 0x00000000;
				if (data->smooth == 1)
				{
					if (data->iter != data->max_iter)
					{
						color1 = get_palette_color(floor(mu), data->palette);
						color2 = get_palette_color(ceil(mu), data->palette);
						data->color = linear_interpolate(color1, color2, mu - floor(mu));
					}
				}
				else
				{
					if (data->iter != data->max_iter)
					{
						color1 = get_palette_color((data->iter), data->palette);
						color2 = get_palette_color((data->iter) + 1, data->palette);
						data->color = linear_interpolate(color1, color2, data->iter
								- floor(data->iter));
					}
				}
				put_pixel_art(data, i, j, data->color);
			}
			j += data->pixel_size;
		}
		i += data->pixel_size;
	}
	return (0);
}
