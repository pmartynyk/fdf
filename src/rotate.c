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

void	bresenham(t_fdf *fdf, t_point pnt1, t_point pnt2)
{
	int deltax;
	int deltay;
	int dirx;
	int diry;
	int error;

	deltax = abs((int)pnt2.x - (int)pnt1.x);
	deltay = abs((int)pnt2.y - (int)pnt1.y);
	dirx = ((int)pnt1.x < (int)pnt2.x ? 1 : -1);
	diry = ((int)pnt1.y < (int)pnt2.y ? 1 : -1);
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

t_point	ft_rotate(t_point pnt, t_fdf *fdf)
{
	t_point	res;
	double	x;
	double	y;
	double	z;

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

t_point	ft_calc(t_point pnt, t_fdf *fdf)
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
