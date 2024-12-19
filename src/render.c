/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:47:45 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/19 11:32:04 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	This function sets the color of a specific pixel in the image buffer.
//	The function essentially translates 2D coordinates (x, y) into a 
//	1D memory address in the image buffer and then writes the color value
//	to that address.  
void	pixel_put(int x, int y, t_img *img, int color)
{
	*(unsigned int *)(img->pixels_ptr + (y * img->line_len)
			+ (x * (img->bpp / 8))) = color;
}

//	This function performs the iterative calculation
//	for a fractal at a given point.
//	If the sequence escapes (goes beyond the escape value)
//	within the iteration limit, the point is not in the set,
//	and it's colored based on how quickly it escaped.
//	If it doesn't escape, it's considered in the set and colored black.

void	calculate_fractal(t_complex z, t_complex c, t_fractal *fractal,
			void (*transform)(t_complex*, t_complex*))
{
	int	i;
	int	color;

	i = 0;
	while (i < fractal->iterations)
	{
		transform(&z, &c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			color = get_color(i, fractal->iterations,
					fractal->color_shift, 0);
			pixel_put(fractal->x, fractal->y, &fractal->img, color);
			return ;
		}
		i++;
	}
	pixel_put(fractal->x, fractal->y, &fractal->img, COLOR_BLACK);
}

//  This function determines which fractal calculation
//	to use based on the selected fractal type. 
static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "mandelbrot", 10))
		handle_mandelbrot(x, y, fractal);
	else if (!ft_strncmp(fractal->name, "julia", 5))
		handle_julia(x, y, fractal);
	else if (!ft_strncmp(fractal->name, "burning_ship", 10))
		handle_burning_ship(x, y, fractal);
	else if (!ft_strncmp(fractal->name, "newton", 6))
		handle_newton(x, y, fractal);
}

//	This function renders the entire fractal by calculating the color
//	for each pixel and displaying the resulting image.
void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			handle_pixel(x, y, fractal);
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->img.img_ptr, 0, 0);
}
// mlx_put_image_to_window(...) function is used to
// display an image in a window. Parameters:
//	fractal->mlx_connection: The MLX connection identifier.
//	fractal->mlx_window: The window where the image will be displayed.
//	fractal->img.img_ptr: The pointer to the image to be displayed.
//	0: The x-coordinate where the image should be placed in the window.
//	0: The y-coordinate where the image should be placed in the window.

// This function takes the image stored in memory (pointed to by
// fractal->img.img_ptr) and draws it onto the specified window
//  (fractal->mlx_window). The image is placed at the coordinates
// (0, 0), which means it starts at the top-left corner of the window.
