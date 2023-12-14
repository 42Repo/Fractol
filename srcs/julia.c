/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:17:42 by asuc              #+#    #+#             */
/*   Updated: 2023/12/14 18:03:17 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	julia(t_data *data)
{
	double			xtemp;
	const double	r = 2.0;
	unsigned int	color1;
	unsigned int	color2;
	int				i;
	int				j;
	double			zx;
	double			zy;
	double			ratio;

	data->min_x = data->center_x - (2.0 / data->zoom_factor);
	data->max_x = data->center_x + (2.0 / data->zoom_factor);
	data->min_y = data->center_y - (2.0 / data->zoom_factor);
	data->max_y = data->center_y + (2.0 / data->zoom_factor);
	i = 0;
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
				zx = map(i, 0, WIDTH, data->min_x, data->max_x);
				zy = map(j, 0, HEIGHT, data->min_y * ratio, data->max_y
						* ratio);
			}
			else
			{
				zx = map(i, 0, WIDTH, data->min_x * ratio, data->max_x * ratio);
				zy = map(j, 0, HEIGHT, data->min_y, data->max_y);
			}
			data->iter = 0;
			while (zx * zx + zy * zy < r * r && data->iter < data->max_iter)
			{
				xtemp = zx * zx - zy * zy;
				zy = 2 * zx * zy + data->c_i;
				zx = xtemp + data->c_r;
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
				put_pixel_art(data, i, j, data->color);
			}
			else if (data->color_mode == 1)
			{
				color1 = get_palette_color(floor(data->iter) + 1,
						data->palette);
				color2 = get_palette_color(floor(data->iter) + 1,
						data->palette);
				data->color = linear_interpolate(color1, color2, data->iter
						- floor(data->iter));
				put_pixel_art(data, i, j, data->color);
			}
			j += data->pixel_size;
		}
		i += data->pixel_size;
	}
	return (0);
}
