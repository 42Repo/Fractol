/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:25:38 by asuc              #+#    #+#             */
/*   Updated: 2023/12/14 17:31:52 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

double	abs_double(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	burningship(t_data *data)
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
				zi = abs_double(2 * zr * zi) + j0;
				zr = ktemp;
				data->iter++;
			}
			if (data->color_mode == 0)
			{
				data->color = 0x00000000;
				if (data->iter != data->max_iter)
				{
					color1 = get_palette_color((data->iter), data->palette);
					color2 = get_palette_color((data->iter) + 1, data->palette);
					data->color = linear_interpolate(color1, color2, data->iter
							- floor(data->iter));
				}
				put_pixel_art(data, i, j, data->color, data->pixel_size);
			}
			else if (data->color_mode == 1)
			{
				color1 = get_palette_color(floor(data->iter) + 1,
						data->palette);
				color2 = get_palette_color(floor(data->iter) + 1,
						data->palette);
				data->color = linear_interpolate(color1, color2, data->iter
						- floor(data->iter));
				put_pixel_art(data, i, j, data->color, data->pixel_size);
			}
			j += data->pixel_size;
		}
		i += data->pixel_size;
	}
	return (0);
}
