/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_julia.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:33:43 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/19 11:30:21 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	This function calculates the Julia set fractal
//	for a given pixel coordinate. 
//	z(n+1) = z(n)^2 + c;
//	z(0) = coordinates:
// {"Classic", -0.7, 0.27015};
// {"Dendrite", -0.8, 0.156};
// {"Spiral", 0.285, 0.01};
// {"Siegel Disk", -0.391, -0.587};
// {"Rabbit", -0.123, 0.745}; 

void	handle_julia(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;

	z.x = (map(x, -2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, 2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;
	c.x = fractal->julia_x;
	c.y = fractal->julia_y;
	fractal->x = x;
	fractal->y = y;
	calculate_fractal(z, c, fractal, mandelbrot_transform);
}
