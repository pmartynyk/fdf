/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 12:56:59 by pmartyny          #+#    #+#             */
/*   Updated: 2019/09/20 19:18:14 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	ft_usage(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 0, 0, 16777215, "Usage:");
	mlx_string_put(fdf->mlx, fdf->win, 0, 20, 16711680, "ESC to exit");
	mlx_string_put(fdf->mlx, fdf->win, 0, 40, 16711680, "ARROWS to move");
	mlx_string_put(fdf->mlx, fdf->win, 0, 60, 16711680,
			"Press 'NUM_PLUS' or 'NUM_MINUS' to zoom");
	mlx_string_put(fdf->mlx, fdf->win, 0, 80, 16711680,
			"Press 'R' to restart");
	mlx_string_put(fdf->mlx, fdf->win, 0, 100, 16711680,
			"Press 'ASDW' to rotate");
	mlx_string_put(fdf->mlx, fdf->win, 0, 120, 16711680,
			"Press '1' or '2' to change projection");
}

void		pixel_put(t_fdf *fdf, int y, int x, int color)
{
	if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
		fdf->imgBuf[y * WIDTH + x] = color;
}

void		ft_draw(t_fdf *fdf)
{
	t_point	pnt;
	int		i;
	int		j;

	i = 0;
	ft_bzero(fdf->imgBuf, WIDTH * HEIGHT * sizeof(int));
	while (i < fdf->mapHeight)
	{
		j = 0;
		while (j < fdf->mapLength)
		{
			pnt = ft_calc(fdf->map[i][j], fdf);
			if (j != fdf->mapLength - 1)
				bresenham(fdf, pnt, ft_calc(fdf->map[i][j + 1], fdf));
			if (i != fdf->mapHeight - 1)
				bresenham(fdf, pnt, ft_calc(fdf->map[i + 1][j], fdf));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->image, 0, 0);
	ft_usage(fdf);
}
