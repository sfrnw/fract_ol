/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:53:13 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/19 11:30:33 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	[[0..1000]] -> [-2..+2] 
//	Performs linear interpolation to map values from one range to another.
double	map(double unscaled_num, double new_min,
		double old_min, double old_max)
{
	double	new_max;

	new_max = -new_min;
	return ((new_max - new_min) * (unscaled_num - old_min)
		/ (old_max - old_min) + new_min);
}

//	Adds two complex numbers.
t_complex	complex_add(t_complex a, t_complex b)
{
	t_complex	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

//	Divides two complex numbers.
t_complex	complex_divide(t_complex a, t_complex b)
{
	t_complex	result;
	double		denominator;

	denominator = b.x * b.x + b.y * b.y;
	result.x = (a.x * b.x + a.y * b.y) / denominator;
	result.y = (a.y * b.x - a.x * b.y) / denominator;
	return (result);
}

//	Subtracts two complex numbers.
t_complex	complex_subtract(t_complex a, t_complex b)
{
	t_complex	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

// Multiplies two complex numbers.
t_complex	complex_multiply(t_complex a, t_complex b)
{
	t_complex	result;

	result.x = a.x * b.x - a.y * b.y;
	result.y = a.x * b.y + a.y * b.x;
	return (result);
}
