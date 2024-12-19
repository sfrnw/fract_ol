/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:47:08 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/19 11:30:26 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define WIDTH 1000
# define HEIGHT 1000
# define COLOR_BLACK 0x000000
# define COLOR_WHITE 0xFFFFFF

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_julia_preset
{
	char	*name;
	double	real;
	double	imag;
}	t_julia_preset;

typedef struct s_fractal
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	double	escape_value;
	int		iterations;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
	int		x;
	int		y;
	int		color_shift;
}	t_fractal;

void		fractal_init(t_fractal *fractal);
int			cycle(t_fractal *fractal);
void		fractal_render(t_fractal *fractal);
void		calculate_fractal(t_complex z, t_complex c, t_fractal *fractal,
				void (*transform)(t_complex*, t_complex*));
void		mandelbrot_transform(t_complex *z, t_complex *c);
void		handle_burning_ship(int x, int y, t_fractal *fractal);
void		handle_julia(int x, int y, t_fractal *fractal);
void		handle_mandelbrot(int x, int y, t_fractal *fractal);
double		map(double unscaled_num, double new_min,
				double old_min, double old_max);
t_complex	complex_add(t_complex a, t_complex b);
t_complex	complex_i_pow(t_complex z);
int			key_handler(int keysym, t_fractal *fractal);
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);
void		handle_mouse_zoom(int button, int mouse_x,
				int mouse_y, t_fractal *fractal);
void		handle_newton(int x, int y, t_fractal *fractal);
int			get_color(int iterations, int max_iterations,
				int color_shift, int root_index);
void		render_newton_fractal(t_fractal *fractal);
t_complex	complex_divide(t_complex a, t_complex b);
t_complex	complex_subtract(t_complex a, t_complex b);
t_complex	complex_multiply(t_complex a, t_complex b);
void		pixel_put(int x, int y, t_img *img, int color);
void		data_init(t_fractal *fractal);

#endif