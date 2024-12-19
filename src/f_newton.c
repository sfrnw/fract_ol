/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_newton.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:41:16 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/19 11:30:24 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	f(z) = z^3 - 1
//	dfz =  f'(z) = 3z^2
//	z(n+1) = z(n) - f(z)/dfz(n)
//  This function applies the Newton fractal
//	transformation to a complex number. 

static void	newton_transform(t_complex *z)
{
	t_complex	fz;
	t_complex	dfz;
	t_complex	quotient;

	fz = complex_multiply(*z, complex_multiply(*z, *z));
	fz.x -= 1;
	dfz = complex_multiply(*z, *z);
	dfz.x *= 3;
	dfz.y *= 3;
	quotient = complex_divide(fz, dfz);
	*z = complex_subtract(*z, quotient);
}

//  This function checks if a complex number is close to
//	one of the roots of the polynomial used in the Newton fractal. 
static int	check_root(t_complex z)
{
	if (fabs(z.x - 1) < 0.001 && fabs(z.y) < 0.001)
		return (0);
	else if (fabs(z.x + 0.5) < 0.001 && fabs(z.y - sqrt(3) / 2) < 0.001)
		return (1);
	else if (fabs(z.x + 0.5) < 0.001 && fabs(z.y + sqrt(3) / 2) < 0.001)
		return (2);
	return (-1);
}

//  This function calculates the Newton fractal for a given pixel coordinate. 
void	handle_newton(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	int			i;
	int			color;
	int			root_index;

	z.x = (map(x, -2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, 2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;
	i = 0;
	root_index = -1;
	while (i < fractal->iterations && root_index == -1)
	{
		newton_transform(&z);
		root_index = check_root(z);
		i++;
	}
	if (root_index != -1)
		color = get_color(i, fractal->iterations,
				fractal->color_shift, root_index);
	else
		color = COLOR_BLACK;
	pixel_put(x, y, &fractal->img, color);
}
