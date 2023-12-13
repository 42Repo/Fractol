/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:21:52 by asuc              #+#    #+#             */
/*   Updated: 2023/12/13 10:34:10 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	hook_key_mouse(int keycode, void *data)
{
	if (keycode == 1)
		apply_zoom(data);
	if (keycode == 2)
		apply_dezoom(data);
	mandelbrot(data);
	return (0);
}

int	hook_key_keyboard(int keycode, void *data)
{
	if (keycode == 41 || keycode == 0)
		close_window(data);
	if (keycode == 87)
		increase_max_iter(data);
	if (keycode == 86)
		decrease_max_iter(data);
	if (keycode == 96)
		set_iteration_to(data, 1000);
	if (keycode == 95)
		set_iteration_to(data, 100);
	if (keycode == 79)
		move_right(data);
	if (keycode == 80)
		move_left(data);
	if (keycode == 81)
		move_down(data);
	if (keycode == 82)
		move_up(data);
	if (keycode == 87 || keycode == 86 || keycode == 96 || keycode == 95
		|| keycode == 79 || keycode == 80 || keycode == 81 || keycode == 82)
		mandelbrot(data);
	return (0);
}
