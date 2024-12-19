/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:29:43 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/19 11:32:21 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	This function calculates a single color component (red, green, or blue) 
//	based on the iteration count, color shift, root index, and phase shift. 
//	It uses a sine wave to create smooth color transitions.
static int	calculate_color_component(double t, int color_shift,
				int root_index, double phase_shift)
{
	return ((int)((sin(t * 5 + color_shift * 0.1 + root_index + phase_shift)
			* 0.5 + 0.5) * 255));
}

// This function ensures that a color value stays within the valid
// range of 0 to 255. 
static int	clamp(int value)
{
	if (value < 0)
		return (0);
	else if (value > 255)
		return (255);
	return (value);
}

//	This function generates a color based on the iteration count, maximum
//	iterations, color shift, and root index. It calculates separate red, 
//	green, and blue components using calculate_color_component and combines
//	them into a single integer representing the RGB color.
int	get_color(int iterations, int max_iterations,
		int color_shift, int root_index)
{
	double	t;
	int		r;
	int		g;
	int		b;
	double	phase_shifts[3];

	phase_shifts[0] = 0;
	phase_shifts[1] = 2.094;
	phase_shifts[2] = 3.141;
	t = (double)iterations / max_iterations;
	r = calculate_color_component(t, color_shift, root_index,
			phase_shifts[(root_index)]);
	g = calculate_color_component(t, color_shift, root_index,
			phase_shifts[(root_index + 1) % 3]);
	b = calculate_color_component(t, color_shift, root_index,
			phase_shifts[(root_index + 2) % 3]);
	r = clamp(r);
	g = clamp(g);
	b = clamp(b);
	return ((r << 16) | (g << 8) | b);
}
