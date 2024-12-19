/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:53:16 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/19 11:59:35 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//  The main of the program. It parses command-line arguments
// to determine which fractal to render and initializes the fractal program. 

int	validate_arguments(int argc, char **argv, t_fractal *fractal)
{
	if (argc == 2 && (!ft_strncmp(argv[1], "mandelbrot", 10)
			|| !ft_strncmp(argv[1], "burning_ship", 12)
			|| !ft_strncmp(argv[1], "newton", 6)))
		return (1);
	if (argc == 4 && !ft_strncmp(argv[1], "julia", 5))
	{
		if (ft_atodbl(argv[2]) >= -2 && ft_atodbl(argv[2]) <= 2
			&& ft_atodbl(argv[3]) >= -2 && ft_atodbl(argv[3]) <= 2)
		{
			fractal->julia_x = ft_atodbl(argv[2]);
			fractal->julia_y = ft_atodbl(argv[3]);
			return (1);
		}
		ft_putstr_fd("Julia values should be between -2 and 2\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (validate_arguments(argc, argv, &fractal))
	{
		fractal.name = argv[1];
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		ft_putstr_fd("Usage:\n\t./fractol mandelbrot\n", 2);
		ft_putstr_fd("\t./fractol julia r_n i_n\n\t./fractol burning_ship", 2);
		ft_putstr_fd("\n\t./fractol newton\n", 2);
		exit(EXIT_FAILURE);
	}
}
