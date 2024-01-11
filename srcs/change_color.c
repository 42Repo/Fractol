/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:56:50 by asuc              #+#    #+#             */
/*   Updated: 2024/01/11 18:01:42 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	change_color_mode(t_data *data)
{
	if (data->color_mode == 0)
		data->color_mode = 1;
	else if (data->color_mode == 1)
		data->color_mode = 0;
}

void	change_smooth(t_data *data)
{
	if (data->smooth == 0)
		data->smooth = 1;
	else if (data->smooth == 1)
		data->smooth = 0;
}
