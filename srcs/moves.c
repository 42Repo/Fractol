/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:22:10 by asuc              #+#    #+#             */
/*   Updated: 2023/12/13 10:34:19 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	move_right(t_data *data)
{
	data->center_x += 0.5 / data->zoom_factor;
}

void	move_left(t_data *data)
{
	data->center_x -= 0.5 / data->zoom_factor;
}

void	move_down(t_data *data)
{
	data->center_y += 0.5 / data->zoom_factor;
}

void	move_up(t_data *data)
{
	data->center_y -= 0.5 / data->zoom_factor;
}
