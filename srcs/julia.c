/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:07:03 by asuc              #+#    #+#             */
/*   Updated: 2023/12/13 11:18:17 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	julia(t_data *data)
{
	int				i;
	int				j;
	double			i0;
	double			j0;
	double			zr;
	double			zi;
	double			ktemp;
	double			ratio;
	// double			log_zn;
	// double			nu;
	// unsigned int	color1;
	// unsigned int	color2;

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
			while (zr * zr + zi * zi <= (1600)
				&& data->iter < data->max_iter)
			{
				ktemp = zr * zr - zi * zi;
				zi = 2 * zr * zi + j0;
				zr = ktemp + i0;
				data->iter++;
			}
			if (data->iter == data->max_iter)
			{
				mlx_pixel_put(data->mlx, data->win, i, j, 0x000000);
			}
			else
				mlx_pixel_put(data->mlx, data->win, i, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	return (0);
}
