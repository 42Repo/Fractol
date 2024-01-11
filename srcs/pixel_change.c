/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:55:20 by asuc              #+#    #+#             */
/*   Updated: 2024/01/11 17:55:31 by asuc             ###   ########.fr       */
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
