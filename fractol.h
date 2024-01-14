/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:59:24 by asuc              #+#    #+#             */
/*   Updated: 2024/01/15 00:24:14 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "Libft/libft.h"
# include "MacroLibX/includes/mlx.h"
# include <math.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 800
# define PALETTE_SIZE 256

typedef struct s_data
{
	void			*win;
	void			*mlx;
	void			*img;
	double			iter;
	double			max_iter;
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
	double			c_r;
	double			c_i;
	int				mode;
	int				color_mode;
	int				smooth;
	int				pixel_size;
}					t_data;

unsigned int		linear_interpolate(unsigned int color1, unsigned int color2,
						double t);
unsigned int		get_palette_color(int index, unsigned int *palette);
void				init_palette(unsigned int *palette);
void				close_window(t_data *data);
int					main(int argc, char **argv);
int					hook_key_mouse(int keycode, void *data);
int					hook_key_keyboard(int keycode, void *data);
void				increase_max_iter(t_data *data);
void				decrease_max_iter(t_data *data);
void				set_iteration_to(t_data *data, int iter);
double				map(double x, double in_min, double in_max, double out_min,
						double out_max);
int					mandelbrot(t_data *data);
void				move_right(t_data *data);
void				move_left(t_data *data);
void				move_down(t_data *data);
void				move_up(t_data *data);
void				apply_zoom(t_data *data);
void				apply_dezoom(t_data *data);
int					julia(t_data *data);
void				change_color_mode(t_data *data);
void				change_smooth(t_data *data);
void				choose_fractal(t_data *data);
void				put_pixel_art(t_data *data, int x, int y,
						unsigned int color);
int					burningship(t_data *data);
void				add_pixel_size(t_data *data);
void				remove_pixel_size(t_data *data);
void				set_pixel_size_to(t_data *data, int pixel_size);
void				hook_key_keyboard_2(int keycode, void *data);
size_t				max_value(size_t nb1, size_t nb2);
double				ft_atod(const char *str);
int					check_input_julia(int argc, char **argv);

#endif
