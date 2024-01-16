/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:40:48 by asuc              #+#    #+#             */
/*   Updated: 2024/01/16 22:12:37 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	base_color(t_data *data)
{
	unsigned int	color1;
	unsigned int	color2;

	if (data->iter != data->max_iter)
	{
		color1 = get_palette_color((data->iter), data->palette);
		color2 = get_palette_color((data->iter) + 1, data->palette);
		data->color = linear_interpolate(color1, color2, data->iter
				- floor(data->iter));
	}
}

void	smooth_color(t_data *data, double mu)
{
	unsigned int	color1;
	unsigned int	color2;

	if (floor(data->iter) != data->max_iter)
	{
		color1 = get_palette_color(floor(mu), data->palette);
		color2 = get_palette_color(ceil(mu), data->palette);
		data->color = linear_interpolate(color1, color2, mu
				- floor(mu));
	}
}
