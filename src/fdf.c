/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:22:48 by pmartyny          #+#    #+#             */
/*   Updated: 2019/09/20 19:18:50 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	ft_init(t_fdf *fdf)
{
	fdf->cam->step = (WIDTH / fdf->mapLength) * 0.8;
	fdf->cam->setx = WIDTH / 2;
	fdf->cam->sety = HEIGHT / 2;
	fdf->angleX = 0;
	fdf->angleY = 0;
}

static int	ft_checkButton2(int button, t_fdf *fdf)
{
	if (button == PROJECTION1)
		fdf->button = 19;
	else if (button == PROJECTION2)
		fdf->button = 18;
	else if (button == MOVEUP)
		fdf->angleY -= 0.05;
	else if (button == MOVEDOOWN)
		fdf->angleY += 0.05;
	else if (button == MOVERIGHT)
		fdf->angleX -= 0.05;
	else if (button == MOVELEFT)
		fdf->angleX += 0.05;
	else if (button == 15)
		ft_init(fdf);
	return (0);
}

static int	ft_checkButton(int button, t_fdf *fdf)
{
	if (button == 53)
		exit(0);
	if (button == 17)
		exit(0);
	if (button == NUM_PLUS)
		fdf->cam->step += 2;
	else if (button == NUM_MINUS)
	{
		fdf->cam->step -= 2;
		fdf->cam->step = (fdf->cam->step <= 0 ? 1 : fdf->cam->step);
	}
	else if (button == KEYDOWN)
		fdf->cam->setx += 5;
	else if (button == KEYLEFT)
		fdf->cam->sety -= 5;
	else if (button == KEYUP)
		fdf->cam->setx -= 5;
	else if (button == KEYRIGHT)
		fdf->cam->sety += 5;
	else
		ft_checkButton2(button, fdf);
	ft_draw(fdf);
	return (0);
}

static int	ft_close(t_fdf *fdf)
{
	(void)fdf;
	exit(0);
}

int			main(int argc, char **argv)
{
	t_fdf *fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	fdf->cam = (t_cam *)malloc(sizeof(t_cam));
	if (argc == 2)
	{
		fdf->mapHeight = 0;
		fdf->mapLength = 0;
		ft_read(argv[1], fdf);
		ft_init(fdf);
		fdf->mlx = mlx_init();
		fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
		fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		fdf->imgBuf = (int *)mlx_get_data_addr(fdf->image,
		&fdf->bits_per_pixel, &fdf->size_line, &fdf->endian);
		ft_draw(fdf);
		mlx_hook(fdf->win, 2, 0, ft_checkButton, fdf);
		mlx_hook(fdf->win, 17, 0, ft_close, fdf);
		mlx_loop(fdf->mlx);
	}
	else
		ft_printf("Usage: ./fdf Map_file!\n");
	return (0);
}
