/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 12:56:59 by pmartyny          #+#    #+#             */
/*   Updated: 2019/09/14 12:57:01 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void ft_put_start(t_fdf *fdf)
{
    fdf->cord.zoom = 10;
    fdf->cord.startX = (WIDHT / 2 - ((fdf->mapHeight * fdf->cord.zoom) / 2));
    fdf->cord.startY = (HEIGHT / 2 - ((fdf->mapLength * fdf->cord.zoom) / 2));
}

static void ft_drawX(t_fdf *fdf, int length)
{
    int d;
    int x;
    int y;

    x = fdf->cord.x1 * fdf->cord.zoom + fdf->cord.startX;
    y = fdf->cord.y1 * fdf->cord.zoom + fdf->cord.startY;
    d = -fdf->cord.lengthX;
    length++;
    while (length--)
    {
        mlx_pixel_put(fdf->mlx, fdf->win, y, x, fdf->map[fdf->cord.x1][fdf->cord.y1].color);
        x += fdf->cord.dx;
        d += 2 * fdf->cord.lengthY;
        if (d > 0)
        {
            d -= 2 * fdf->cord.lengthX;
            y += fdf->cord.dy;
        }
    }
}

static void ft_drawY(t_fdf *fdf, int length)
{
    int d;
    int x;
    int y;

    x = fdf->cord.x1 * fdf->cord.zoom + fdf->cord.startX;
    y = fdf->cord.y1 * fdf->cord.zoom + fdf->cord.startY;

    d = -fdf->cord.lengthY;
    length++;
    while (length--)
    {
        mlx_pixel_put(fdf->mlx, fdf->win, y, x, fdf->map[fdf->cord.x1][fdf->cord.y1].color);
        y += fdf->cord.dy;
        d += 2 * fdf->cord.lengthX;
        if (d > 0)
        {
            d -= 2 * fdf->cord.lengthY;
            x += fdf->cord.dx;
        }
    }
}

static void ft_init(t_fdf *fdf)
{
    fdf->cord.dx = (fdf->cord.x2 - fdf->cord.x1 >= 0 ? 1 : -1);
    fdf->cord.dy = (fdf->cord.y2 - fdf->cord.y1 >= 0 ? 1 : -1);
    fdf->cord.lengthX = abs((fdf->cord.x2 * fdf->cord.zoom + fdf->cord.startX) - (fdf->cord.x1 * fdf->cord.zoom + fdf->cord.startX));
    fdf->cord.lengthY = abs((fdf->cord.y2 * fdf->cord.zoom + fdf->cord.startY) - (fdf->cord.y1 * fdf->cord.zoom + fdf->cord.startY));
}

void ft_draw_line(t_fdf *fdf)
{
    int length;

    ft_init(fdf);
    length = (fdf->cord.lengthX > fdf->cord.lengthY ? fdf->cord.lengthX : fdf->cord.lengthY);
    if (length == 0)
        mlx_pixel_put(fdf->mlx, fdf->win, fdf->cord.y1, fdf->cord.x1, 0x32a852);
    if (fdf->cord.lengthY <= fdf->cord.lengthX)
        ft_drawX(fdf, length);
    else
        ft_drawY(fdf, length);
}

void ft_draw(t_fdf *fdf)
{
    int i;
    int j;

    i = 0;
    fdf->image = mlx_new_image(fdf->mlx, WIDHT, HEIGHT);
    fdf->simage = mlx_get_data_addr(fdf->image, &fdf->bits_per_pixel, &fdf->size_line, &fdf->endian);
    ft_put_start(fdf);
    while (i < fdf->mapHeight)
    {
        j = 0;
        while (j < fdf->mapLength)
        {
            fdf->cord.x1 = i;
            fdf->cord.y1 = j;
            fdf->cord.x2 = i;
            fdf->cord.y2 = abs(j - 1);
            ft_draw_line(fdf);
            fdf->cord.x2 = abs(i - 1);
            fdf->cord.y2 = j;
            ft_draw_line(fdf);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->simage, 0, 0);
}
