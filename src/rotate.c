/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:16:12 by pmartyny          #+#    #+#             */
/*   Updated: 2019/09/17 15:16:14 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void ft_rotateX(t_fdf *fdf)
{
    int i;
    int j;
    double xyz[3];
    // double tmpX = 0;
    // double tmpY = 0;
    // double tmpZ = 0;

    i = 0;
    while (i < fdf->mapHeight)
    {
        j = 0;
        while (j < fdf->mapLength)
        {
            xyz[0] = fdf->map[i][j].x;
            xyz[2] = fdf->map[i][j].z;
            // printf("x=%f y= %f z= %f before\n", fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i][j].z);
            fdf->map[i][j].x = xyz[0] * cos(fdf->angleY) + xyz[2] * sin(fdf->angleY);
            fdf->map[i][j].z = xyz[0] * -sin(fdf->angleY) + xyz[2] * cos(fdf->angleY);
            xyz[1] = fdf->map[i][j].y;
            xyz[2] = fdf->map[i][j].z;
            fdf->map[i][j].y = xyz[1] * cos(fdf->angleX) - xyz[2] * sin(fdf->angleX);
            fdf->map[i][j].z = xyz[1] * -sin(fdf->angleX) + xyz[2] * cos(fdf->angleX);

            // printf("x=%f y= %f z= %f after\n", fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i][j].z);
            j++;
        }
        i++;
    }
}