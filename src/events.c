/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:11:21 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/19 11:30:16 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	This function handles the closing of the fractal window.
//	It cleans up resources by destroying the image, window, and display,
//	then exits the program.
int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
}

//	This function handles keyboard input. It responds to various key presses
//	to move the fractal view, change the fractal type, or exit the program.
int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	else if (keysym == XK_Left)
		fractal->shift_x -= 0.5 * fractal->zoom;
	else if (keysym == XK_Right)
		fractal->shift_x += 0.5 * fractal->zoom;
	else if (keysym == XK_Up)
		fractal->shift_y -= 0.5 * fractal->zoom;
	else if (keysym == XK_Down)
		fractal->shift_y += 0.5 * fractal->zoom;
	else if (keysym == XK_m || keysym == XK_n
		|| keysym == XK_j || keysym == XK_b)
	{
		data_init(fractal);
		if (keysym == XK_m)
			fractal->name = "mandelbrot";
		else if (keysym == XK_n)
			fractal->name = "newton";
		else if (keysym == XK_j)
			fractal->name = "julia";
		else if (keysym == XK_b)
			fractal->name = "burning_ship";
	}
	return (fractal_render(fractal), 0);
}

//	This function handles mouse input. It allows zooming in and out using
//	the mouse wheel and adjusting the iteration count using mouse buttons.
int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	if (button == Button5)
		fractal->zoom *= 1.05;
	else if (button == Button4)
		fractal->zoom *= 0.95;
	else if (button == Button1)
	{
		fractal->iterations += 1;
		if (fractal->iterations > 100)
			fractal->iterations = 100;
	}
	else if (button == Button3)
	{
		fractal->iterations -= 1;
		if (fractal->iterations < 1)
			fractal->iterations = 1;
	}
	fractal_render(fractal);
	return (0);
}

// This function is called repeatedly to create animation effects.
// It gradually shifts colors and updates Julia set parameters over time. 
int	cycle(t_fractal *fractal)
{
	static int	frame_count = 0;
	static int	direction = 5;

	frame_count++;
	if (frame_count >= 60)
	{
		fractal->color_shift = (fractal->color_shift + 1) % 360;
		fractal->julia_x += direction * 0.01;
		fractal->julia_y += direction * 0.01;
		if (fractal->julia_x >= 2.0 || fractal->julia_x <= -2.0
			|| fractal->julia_y >= 2.0 || fractal->julia_y <= -2.0)
		{
			direction *= -1;
		}
		fractal_render(fractal);
		frame_count = 0;
	}
	return (0);
}
