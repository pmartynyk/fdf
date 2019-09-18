/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:22:48 by pmartyny          #+#    #+#             */
/*   Updated: 2019/03/28 14:22:49 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int ft_checkButton(int button, t_fdf *fdf)
{
    (void)fdf;
    if (button == 53)
        exit(0);
    if (button == 17)
        exit(0);
    // if (button == NUM_PLUS)
    // {
    //     fdf->cord.zoom += 2;
    //     // ft_draw(fdf);
    // }
    // else if (button == NUM_MINUS)
    // {
    //     fdf->cord.zoom -= 2;
    //     fdf->cord.zoom = (fdf->cord.zoom <= 0 ? 1 : fdf->cord.zoom);
    //     // ft_draw(fdf);
    // }
    // else if (button == KEYDOWN)
    // {
    //     fdf->cord.wid += 5;
    //     // ft_draw(fdf);
    // }
    // else if (button == KEYLEFT)
    // {
    //     fdf->cord.hei -= 5;
    //     // ft_draw(fdf);
    // }
    // else if (button == KEYUP)
    // {
    //     fdf->cord.wid -= 5;
    //     // ft_draw(fdf);
    // }
    // else if (button == KEYRIGHT)
    // {
    //     fdf->cord.hei += 5;
    // }
    if (button == O_BUTTON)
    {
        fdf->button = 19;
    }
    ft_draw(fdf);
    return (0);
}

static int ft_close(t_fdf *fdf)
{
    (void)fdf;
    exit(0);
}

// static void ft_put_start(t_fdf *fdf)
// {
//     fdf->cord.zoom = 10;
//     fdf->cord.startX = (WIDTH / 2 - ((fdf->mapHeight * fdf->cord.zoom) / 2));
//     fdf->cord.startY = (HEIGHT / 2 - ((fdf->mapLength * fdf->cord.zoom) / 2));
// }

int main(int argc, char **argv)
{
    t_fdf *fdf;
    fdf = (t_fdf *)malloc(sizeof(t_fdf));
    fdf->cam = ft_memalloc(sizeof(t_cam));
    if (argc == 2)
    {
        ft_read(argv[1], fdf);
        fdf->cam->step = 10;
        fdf->cam->setx = (WIDTH / 2 - ((fdf->mapHeight * fdf->cam->step) / 2));
        fdf->cam->sety = (HEIGHT / 2 - ((fdf->mapLength * fdf->cam->step) / 2));
        fdf->mlx = mlx_init();
        fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
        fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
        fdf->imgBuf = (int *)mlx_get_data_addr(fdf->image, &fdf->bits_per_pixel, &fdf->size_line, &fdf->endian);
        ft_draw(fdf);
        mlx_hook(fdf->win, 2, 0, ft_checkButton, fdf);
        mlx_hook(fdf->win, 17, 0, ft_close, fdf);
        mlx_loop(fdf->mlx);
    }
    else
    {
        ft_printf("Error!\n");
    }

    return (0);
}