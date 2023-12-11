/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:55:00 by asuc              #+#    #+#             */
/*   Updated: 2023/12/12 00:29:40 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	close_window(t_data *data)
{
	mlx_loop_end(data->mlx);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
	}
	exit(0);
}

int	hook_key(int keycode, void *data)
{
	if (keycode == 41)
		close_window(data);
	ft_printf("keycode = %d\n", keycode);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		e;

	(void)argc;
	(void)argv;
	int *i;
	i = malloc(sizeof(int));
	data = malloc(sizeof(t_data));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 400, 400, "Fractol");
	mlx_pixel_put(data->mlx, data->win, 200, 200, 0x00FFFFFF);
	e = mlx_on_event(data->mlx, data->win, 0, hook_key, data);
	mlx_loop(data->mlx);
	return (0);
}
