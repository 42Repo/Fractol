/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:55:00 by asuc              #+#    #+#             */
/*   Updated: 2023/12/12 03:03:56 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <complex.h>

void	close_window(t_data *data)
{
	mlx_loop_end(data->mlx);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
	}
	free(data);
	exit(0);
}

void	free_all(t_data *data)
{
	free(data->tab);
}

int	hook_key(int keycode, void *data)
{
	if (keycode == 41)
	{
		free_all(data);
		close_window(data);
	}
	ft_printf("keycode = %d\n", keycode);
	return (0);
}

int mandelbrot()
{}

int complex_calcul(t_data *data,

int	main(int argc, char **argv)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	data->tab = malloc(sizeof(int) * 10);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 400, 400, "Fractol");
	data->img = mlx_new_image(data->mlx, 400, 400);
	mlx_pixel_put(data->mlx, data->win, 200, 200, 0x00FFFFFF);
	mlx_on_event(data->mlx, data->win, 0, hook_key, data);
	mlx_loop(data->mlx);
	return (0);
}
