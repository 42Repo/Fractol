/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:59:24 by asuc              #+#    #+#             */
/*   Updated: 2023/12/13 05:41:27 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "Libft/libft.h"
# include "MacroLibX/includes/mlx.h"
# include <math.h>

typedef struct s_data
{
	void			*win;
	void			*mlx;
	void			*img;
	int				iter;
	int				max_iter;
	unsigned int	color;
	double			zoom_factor;
	double			center_x;
	double			center_y;
	int				mouse_x;
	int				mouse_y;
	double			min_x;
	double			max_x;
	double			min_y;
	double			max_y;
	unsigned int	*palette;
}	t_data;

void	close_window(t_data *data);
int		key_hook(int keycode, void *data);
int		main(int argc, char **argv);

#endif
