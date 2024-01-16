/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:40:36 by asuc              #+#    #+#             */
/*   Updated: 2024/01/17 00:09:06 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

double	abs_double(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	set_min_max(t_data *data)
{
	data->min_x = data->center_x - (2.0 / data->zoom_factor);
	data->max_x = data->center_x + (2.0 / data->zoom_factor);
	data->min_y = data->center_y - (2.0 / data->zoom_factor);
	data->max_y = data->center_y + (2.0 / data->zoom_factor);
}

double	set_ratio(void)
{
	double	ratio;

	if (WIDTH > HEIGHT)
		ratio = (double)HEIGHT / (double)WIDTH;
	else
		ratio = (double)WIDTH / (double)HEIGHT;
	return (ratio);
}

void	calculate_map(double *i0, double *j0, t_data *data)
{
	if (WIDTH > HEIGHT)
	{
		(*i0) = map(data->i, WIDTH, data->min_x, data->max_x);
		(*j0) = map(data->j, HEIGHT, data->min_y * data->ratio, data->max_y
				* data->ratio);
	}
	else
	{
		(*i0) = map(data->i, WIDTH, data->min_x * data->ratio, data->max_x
				* data->ratio);
		(*j0) = map(data->j, HEIGHT, data->min_y, data->max_y);
	}
}

double	map(double x, double in_max, double out_min, double out_max)
{
	return (((x - 0) * (out_max - out_min) / (in_max - 0) + out_min));
}
