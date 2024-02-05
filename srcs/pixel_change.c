/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:55:20 by asuc              #+#    #+#             */
/*   Updated: 2024/02/05 18:24:46 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	add_pixel_size(t_data *data)
{
	if (data->pixel_size < 16)
		data->pixel_size++;
}

void	remove_pixel_size(t_data *data)
{
	if (data->pixel_size > 1)
		data->pixel_size--;
}

void	set_pixel_size_to(t_data *data, int pixel_size)
{
	data->pixel_size = pixel_size;
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
				color += 0xFF000000;
				mlx_set_image_pixel(data->mlx, data->img, x + dx, y + dy, color);
			}
			dy++;
		}
		dx++;
	}
}
