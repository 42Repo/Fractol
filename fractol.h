/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:59:24 by asuc              #+#    #+#             */
/*   Updated: 2023/12/12 02:55:57 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "Libft/libft.h"
# include "MacroLibX/includes/mlx.h"

typedef struct s_data
{
	void	*win;
	void	*mlx;
	int		*tab;
	void	*img;
}	t_data;

void	close_window(t_data *data);
int		key_hook(int keycode, void *data);
int		main(int argc, char **argv);

#endif
