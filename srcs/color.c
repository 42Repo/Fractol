/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:20:38 by asuc              #+#    #+#             */
/*   Updated: 2023/12/15 01:22:08 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

unsigned int	linear_interpolate(unsigned int color1, unsigned int color2,
		double t)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)((1 - t) * ((color1 >> 16) & 0xFF) + t
			* ((color2 >> 16) & 0xFF));
	g = (unsigned int)((1 - t) * ((color1 >> 8) & 0xFF) + t
			* ((color2 >> 8) & 0xFF));
	b = (unsigned int)((1 - t) * (color1 & 0xFF) + t * (color2 & 0xFF));
	return ((r << 16) | (g << 8) | b);
}

unsigned int	get_palette_color(int index, unsigned int *palette)
{
	return (palette[index % PALETTE_SIZE]);
}

void	init_palette(unsigned int *palette)
{
	int				i;
	double			t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	i = 0;
	while (i < PALETTE_SIZE)
	{
		t = (double)i / (PALETTE_SIZE - 1);
		r = (unsigned int)(9 * (1 - t) * t * t * t * 255);
		g = (unsigned int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (unsigned int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		palette[i] = (r << 16) | (g << 8) | b;
		i++;
	}
}
