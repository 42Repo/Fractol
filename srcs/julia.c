/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:17:42 by asuc              #+#    #+#             */
/*   Updated: 2023/12/13 14:36:18 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int julia(t_data *data)
{
	int i, j;
	double zx, zy;
	double xtemp;
	const double r = 2.0;
	unsigned int	color1;
	unsigned int	color2;

	data->min_x = data->center_x - (2.0 / data->zoom_factor);
	data->max_x = data->center_x + (2.0 / data->zoom_factor);
	data->min_y = data->center_y - (2.0 / data->zoom_factor);
	data->max_y = data->center_y + (2.0 / data->zoom_factor);
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			zx = map(i, 0, WIDTH, data->min_x, data->max_x);
			zy = map(j, 0, HEIGHT, data->min_y, data->max_y);
			data->iter = 0;
			while (zx * zx + zy * zy < r * r && data->iter < data->max_iter)
			{
				xtemp = zx * zx - zy * zy;
				zy = 2 * zx * zy + data->c_i;
				zx = xtemp + data->c_r;
				data->iter++;
			}
			data->color = 0x00000000;
			if (data->iter != data->max_iter)
			{
				color1 = get_palette_color(floor(data->iter), data->palette);
				color2 = get_palette_color(floor(data->iter) + 1, data->palette);
				data->color = linear_interpolate(color1, color2, data->iter
						- floor(data->iter));
			}
			mlx_pixel_put(data->mlx, data->win, i, j, data->color);
			j++;
		}
		i++;
	}
	return (0);
}
