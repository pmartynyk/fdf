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

static void pixel_put(t_fdf *fdf, int y, int x, int color)
{
    if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
        fdf->imgBuf[y * WIDTH + x] = color;
}

void bresenham(t_fdf *fdf, t_point pnt1, t_point pnt2)
{
    int deltax;
    int deltay;
    int dirx;
    int diry;
    int error;

    deltax = abs((int)pnt2.x - (int)pnt1.x);
    deltay = abs((int)pnt2.y - (int)pnt1.y);
    dirx = (int)pnt1.x < (int)pnt2.x ? 1 : -1;
    diry = (int)pnt1.y < (int)pnt2.y ? 1 : -1;
    error = deltax - deltay;
    while (pnt1.x != pnt2.x || pnt1.y != pnt2.y)
    {
        pixel_put(fdf, (int)pnt1.x, (int)pnt1.y, pnt1.color);
        if (error * 2 > -deltay)
        {
            error -= deltay;
            pnt1.x += dirx;
        }
        else
        {
            error += deltax;
            pnt1.y += diry;
        }
    }
}

static t_point ft_rotate(t_point pnt, t_fdf *fdf)
{
    t_point res;
    double x;
    double y;
    double z;

    x = pnt.x;
    z = pnt.z;
    res.x = x * cos(fdf->angleY) + z * sin(fdf->angleY);
    res.z = x * -sin(fdf->angleY) + z * cos(fdf->angleY);
    y = pnt.y;
    z = res.z;
    res.y = y * cos(fdf->angleX) - z * sin(fdf->angleX);
    res.z = y * sin(fdf->angleX) + z * cos(fdf->angleX);
    res.color = pnt.color;
    return (res);
}

t_point ft_expose(t_point pnt, t_fdf *fdf)
{
    double x;

    pnt.x -= (double)(fdf->mapHeight - 1) / 2;
    x = pnt.x;
    pnt.y -= (double)(fdf->mapLength - 1) / 2;
    
    if (fdf->button == 19)
    {
        pnt.x = (pnt.x - pnt.y);
        pnt.y = (x + pnt.y);
    }
    pnt = ft_rotate(pnt, fdf);
    pnt.x *= fdf->cam->step;
    if (fdf->button == 19)
        pnt.y *= fdf->cam->step / 2;
    else
        pnt.y *= fdf->cam->step;
    pnt.x += fdf->cam->setx;
    pnt.y += fdf->cam->sety;
    pnt.x = (int)pnt.x;
    pnt.y = (int)pnt.y;
    return (pnt);
}

void ft_draw(t_fdf *fdf)
{
    t_point pnt;
    int i;
    int j;

    i = 0;
    ft_bzero(fdf->imgBuf, WIDTH * HEIGHT * sizeof(int));
    while (i < fdf->mapHeight)
    {
        j = 0;
        while (j < fdf->mapLength)
        {
            // ft_printf("%f %f %f\n", fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i][j].z);
            pnt = ft_expose(fdf->map[i][j], fdf);
            if (j != fdf->mapLength - 1)
                bresenham(fdf, pnt, ft_expose(fdf->map[i][j + 1], fdf));
            if (i != fdf->mapHeight - 1)
                bresenham(fdf, pnt, ft_expose(fdf->map[i + 1][j], fdf));
            // ft_printf("%f %f\n", pnt.x, pnt.y);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->image, 0, 0);
    // usage_string(fdf);
}

// static void pixel_put(t_fdf *fdf, int x, int y)
// {
//     if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
//         fdf->imgBuf[y * WIDTH + x] = fdf->map[fdf->cord.x1][fdf->cord.y1].color;
// }

// static void ft_drawX(t_fdf *fdf, int length)
// {
//     int d;
//     int x;
//     int y;

//     x = fdf->cord.x1 * fdf->cord.zoom + fdf->cord.startX;
//     y = fdf->cord.y1 * fdf->cord.zoom + fdf->cord.startY;
//     d = -fdf->cord.lengthX;
//     length++;
//     while (length--)
//     {
//         pixel_put(fdf, y + fdf->cord.hei, x + fdf->cord.wid);
//         x += fdf->cord.dx;
//         d += 2 * fdf->cord.lengthY;
//         if (d > 0)
//         {
//             d -= 2 * fdf->cord.lengthX;
//             y += fdf->cord.dy;
//         }
//     }
// }

// static void ft_drawY(t_fdf *fdf, int length)
// {
//     int d;
//     int x;
//     int y;

//     x = fdf->cord.x1 * fdf->cord.zoom + fdf->cord.startX;
//     y = fdf->cord.y1 * fdf->cord.zoom + fdf->cord.startY;

//     d = -fdf->cord.lengthY;
//     length++;
//     while (length--)
//     {
//         pixel_put(fdf, y + fdf->cord.hei, x + fdf->cord.wid);
//         y += fdf->cord.dy;
//         d += 2 * fdf->cord.lengthX;
//         if (d > 0)
//         {
//             d -= 2 * fdf->cord.lengthY;
//             x += fdf->cord.dx;
//         }
//     }
// }

// static void ft_init(t_fdf *fdf)
// {
//     fdf->cord.dx = (fdf->cord.x2 - fdf->cord.x1 >= 0 ? 1 : -1);
//     fdf->cord.dy = (fdf->cord.y2 - fdf->cord.y1 >= 0 ? 1 : -1);
//     fdf->cord.lengthX = abs((fdf->cord.x2 * fdf->cord.zoom + fdf->cord.startX) - (fdf->cord.x1 * fdf->cord.zoom + fdf->cord.startX));
//     fdf->cord.lengthY = abs((fdf->cord.y2 * fdf->cord.zoom + fdf->cord.startY) - (fdf->cord.y1 * fdf->cord.zoom + fdf->cord.startY));
// }

// void ft_draw_line(t_fdf *fdf)
// {
//     int length;

//     ft_init(fdf);
//     fdf->cord.startX = (WIDTH / 2 - ((fdf->mapHeight * fdf->cord.zoom) / 2));
//     fdf->cord.startY = (HEIGHT / 2 - ((fdf->mapLength * fdf->cord.zoom) / 2));

//     length = (fdf->cord.lengthX > fdf->cord.lengthY ? fdf->cord.lengthX : fdf->cord.lengthY);
//     if (length == 0)
//         pixel_put(fdf, fdf->cord.y1 + fdf->cord.hei, fdf->cord.x1 + fdf->cord.wid);
//     if (fdf->cord.lengthY <= fdf->cord.lengthX)
//         ft_drawX(fdf, length);
//     else
//         ft_drawY(fdf, length);
// }

// void ft_draw(t_fdf *fdf)
// {
//     int i;
//     int j;

//     i = 0;
//     ft_bzero(fdf->imgBuf, WIDTH * HEIGHT * sizeof(int));
//     while (i < fdf->mapHeight)
//     {
//         j = 0;
//         while (j < fdf->mapLength)
//         {
//             fdf->cord.x1 = fdf->map[i][j].x;
//             fdf->cord.y1 = fdf->map[i][j].y;
//             if (j != fdf->mapLength - 1)
//             {
//                 fdf->cord.x2 = fdf->map[i][j].x;
//                 fdf->cord.y2 = abs(fdf->map[i][j + 1].y);
//                 ft_draw_line(fdf);
//             }
//             if (i != fdf->mapHeight - 1)
//             {
//                 fdf->cord.x2 = abs(fdf->map[i + 1][j].x);
//                 fdf->cord.y2 = fdf->map[i][j].y;
//                 ft_draw_line(fdf);
//             }
//             j++;
//         }
//         i++;
//     }
//     mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->image, 0, 0);
// }