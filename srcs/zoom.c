/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:26:13 by asuc              #+#    #+#             */
/*   Updated: 2024/01/17 00:08:12 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	apply_zoom(t_data *data)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;

	mlx_mouse_get_pos(data->mlx, &data->mouse_x, &data->mouse_y);
	zoom_factor = 1.2;
	mouse_re = map(data->mouse_x, WIDTH, data->center_x - 2
			/ data->zoom_factor, data->center_x + 2 / data->zoom_factor);
	mouse_im = map(data->mouse_y, HEIGHT, data->center_y - 2
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
	zoom_factor = 0.8;
	mouse_re = map(data->mouse_x, WIDTH, data->center_x - 2
			/ data->zoom_factor, data->center_x + 2 / data->zoom_factor);
	mouse_im = map(data->mouse_y, HEIGHT, data->center_y - 2
			/ data->zoom_factor, data->center_y + 2 / data->zoom_factor);
	data->zoom_factor *= zoom_factor;
	data->center_x = mouse_re + (data->center_x - mouse_re) / zoom_factor;
	data->center_y = mouse_im + (data->center_y - mouse_im) / zoom_factor;
}
