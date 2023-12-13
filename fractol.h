/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:59:24 by asuc              #+#    #+#             */
/*   Updated: 2023/12/13 01:09:30 by asuc             ###   ########.fr       */
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
	int				*tab;
	void			*img;
	int				iter;
	int				max_iter;
	unsigned int	color;

}	t_data;

void	close_window(t_data *data);
int		key_hook(int keycode, void *data);
int		main(int argc, char **argv);

#endif
