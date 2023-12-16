/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:21:52 by asuc              #+#    #+#             */
/*   Updated: 2023/12/16 20:27:04 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	choose_fractal(t_data *data)
{
	if (data->mode == 0)
		julia(data);
	else if (data->mode == 1)
		mandelbrot(data);
	else if (data->mode == 2)
		burningship(data);
}

int	hook_key_mouse(int keycode, void *data)
{
	if (keycode == 1)
		apply_zoom(data);
	if (keycode == 2)
		apply_dezoom(data);
	choose_fractal(data);
	return (0);
}

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


int	hook_key_keyboard(int keycode, void *data)
{
	if (keycode == 41 || keycode == 0)
		close_window(data);
	if (keycode == 87)
		increase_max_iter(data);
	if (keycode == 86)
		decrease_max_iter(data);
	if (keycode == 96)
		set_iteration_to(data, 2000);
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
	if (keycode == 89)
		change_color_mode(data);
	if (keycode == 90)
		change_smooth(data);
	if (keycode == 91)
		add_pixel_size(data);
	if (keycode == 92)
		remove_pixel_size(data);
	if (keycode == 93)
		set_pixel_size_to(data, 1);
	if (keycode == 87 || keycode == 86 || keycode == 96 || keycode == 95
		|| keycode == 79 || keycode == 80 || keycode == 81 || keycode == 82
		|| keycode == 89 || keycode == 90 || keycode == 91 || keycode == 92
		|| keycode == 93 || keycode == 94)
		choose_fractal(data);
	return (0);
}
