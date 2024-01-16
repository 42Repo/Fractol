/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:17:42 by asuc              #+#    #+#             */
/*   Updated: 2024/01/16 23:14:16 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static void	calculate(t_data *data, double *zr, double *zi)
{
	double	i0;
	double	j0;
	double	ktemp;

	calculate_map(&i0, &j0, data);
	(*zr) = i0;
	(*zi) = j0;
	data->iter = 0;
	data->iter = 0;
	while ((*zr) * (*zr) + (*zi) * (*zi) < 4 && data->iter < data->max_iter)
	{
		ktemp = (*zr) * (*zr) - (*zi) * (*zi);
		(*zi) = 2 * (*zr) * (*zi) + data->c_i;
		(*zr) = ktemp + data->c_r;
		data->iter++;
	}
}

static double	calculate_julia(t_data *data)
{
	double	log_zn;
	double	nu;
	double	zr;
	double	zi;

	calculate(data, &zr, &zi);
	if (data->smooth == 1)
	{
		log_zn = log(zr * zr + zi * zi) / 2;
		nu = log(log_zn / log(2)) / log(2);
		nu = data->iter + (double)1 - nu;
		return (nu);
	}
	return (0);
}

static int	julia_loop(t_data *data)
{
	double			mu;

	mu = calculate_julia(data);
	if (data->color_mode == 0)
	{
		data->color = 0x00000000;
		if (data->smooth == 1)
			smooth_color(data, mu);
		else
			base_color(data);
		put_pixel_art(data, data->i, data->j, data->color);
	}
	return (0);
}

int	julia(t_data *data)
{
	set_min_max(data);
	data->ratio = set_ratio();
	data->i = 0;
	while (data->i < WIDTH)
	{
		data->j = 0;
		while (data->j < HEIGHT)
		{
			julia_loop(data);
			data->j += data->pixel_size;
		}
		data->i += data->pixel_size;
	}
	return (0);
}
