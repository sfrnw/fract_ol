/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:58:25 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/19 11:32:12 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//  This function handles memory allocation errors by displaying
//	an error message and closing the program. 
static void	malloc_error(t_fractal *fractal)
{
	ft_putstr_fd("Error: Memory allocation failed\n", 2);
	close_handler(fractal);
}

// This function initializes the fractal parameters with default values. 
void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->iterations = 20;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->color_shift = 0;
	fractal->x = 0;
	fractal->y = 0;
	if (!fractal->julia_x)
		fractal->julia_x = 0.285;
	if (!fractal->julia_y)
		fractal->julia_x = 0.01;
}

//	 This function sets up event handlers for keyboard and mouse input. 
static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window, KeyPress, KeyPressMask, key_handler, fractal);
	mlx_hook(fractal->mlx_window, ButtonPress, ButtonPressMask,
		mouse_handler, fractal);
	mlx_hook(fractal->mlx_window, DestroyNotify, StructureNotifyMask,
		close_handler, fractal);
	mlx_loop_hook(fractal->mlx_connection, cycle, fractal);
}

//  This function initializes the fractal program by setting up the MLX library,
//	creating a window, and initializing the image buffer. 

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if (fractal->mlx_connection == NULL)
		malloc_error(fractal);
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection,
			WIDTH, HEIGHT, fractal->name);
	if (fractal->mlx_window == NULL)
	{
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		malloc_error(fractal);
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection,
			WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
		malloc_error(fractal);
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.line_len,
			&fractal->img.endian);
	events_init(fractal);
	data_init(fractal);
}

//mlx_init():
// This function initializes the MLX library and establishes a connection to
// the X server. It returns a void pointer that serves as the MLX connection 
// identifier, which is necessary for subsequent MLX function call
//mlx_new_window(...):
// This function creates a new window on the screen. It takes four parameters:
//     The MLX connection identifier
//     The width of the window
//     The height of the window
//     The title of the window
//     It returns a pointer to the newly created window
// mlx_destroy_display(...):
//     This function is called if window creation fails. It cleans up the MLX 
//     connection and frees associated resources
//mlx_new_image(fractal->mlx_connection, WIDTH, HEIGHT):
// This function creates a new image in memory. It takes three parameters:
//     The MLX connection identifier
//     The width of the image
//     The height of the image
//     It returns a pointer to the new image
// mlx_get_data_addr():
// This function retrieves information about the created image.
// It takes four parameters:
//     The image pointer
//     A pointer to store the bits per pixel
//     A pointer to store the size of a line in bytes
//     A pointer to store the endian information
// It returns the memory address of the image data, allowing direct
// pixel manipulation