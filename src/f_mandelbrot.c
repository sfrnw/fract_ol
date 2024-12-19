/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_mandelbrot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:33:26 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/19 11:30:22 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	This function applies the Mandelbrot set
//	transformation to a complex number. 
//	z(n+1) = z(n)^2 + c;
//	z(0) = 0;
void	mandelbrot_transform(t_complex *z, t_complex *c)
{
	*z = complex_add(complex_multiply(*z, *z), *c);
}

//	This function calculates the Mandelbrot set
//	fractal for a given pixel coordinate. 
void	handle_mandelbrot(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;

	z.x = 0;
	z.y = 0;
	c.x = (map(x, -2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	c.y = (map(y, 2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;
	fractal->x = x;
	fractal->y = y;
	calculate_fractal(z, c, fractal, mandelbrot_transform);
}
