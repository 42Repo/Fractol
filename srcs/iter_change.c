/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:26:42 by asuc              #+#    #+#             */
/*   Updated: 2023/12/13 10:34:12 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	increase_max_iter(t_data *data)
{
	data->max_iter += 10;
}

void	decrease_max_iter(t_data *data)
{
	data->max_iter -= 10;
}

void	set_iteration_to(t_data *data, int iter)
{
	data->max_iter = iter;
}
