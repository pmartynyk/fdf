/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:23:58 by pmartyny          #+#    #+#             */
/*   Updated: 2019/03/28 14:24:00 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include "../libft_printf/includes/ft_printf.h"
#include "mlx.h"
#include <fcntl.h>
#include <math.h>
#include <sys/ioctl.h>

#define KEYUP 126
#define KEYDOWN 125
#define KEYLEFT 123
#define KEYRIGHT 124
#define O_BUTTON 31
#define NUM_PLUS 69
#define NUM_MINUS 78

#define WIDTH 1000
#define HEIGHT 1000

typedef struct	s_cam
{
	double		setx;
	double		sety;
	double		x;
	double		y;
	double		step;
}				t_cam;

typedef struct s_point
{
    double x;
    double y;
    double z;
    int color;
} t_point;

typedef struct s_fdf
{
    void *win;
    void *mlx;
    void *image;
    int bits_per_pixel;
    int size_line;
    int endian;
    int *imgBuf;
    t_point **map;
    int mapLength;
    int mapHeight;    
    double angleX;
    double angleY;
    int button;
    t_cam *cam;
    t_point *pnt1;
    t_point *pnt2;
} t_fdf;

//read.c
void ft_read(char *argv, t_fdf *fdf);
void ft_free(char **map);


//draw
void pixel_put(t_fdf *fdf, int y, int x, int color);
void ft_draw(t_fdf *fdf);

//rotate.c
void changeAltitude(int n, t_fdf *fdf);
void bresenham(t_fdf *fdf, t_point pnt1, t_point pnt2);
t_point ft_rotate(t_point pnt, t_fdf *fdf);
t_point ft_calc(t_point pnt, t_fdf *fdf);




#endif
