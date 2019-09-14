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

// static void	ft_mlx(t_fdf *fdf)
// {
// 	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->image, 0, 0);
// 	// mlx_string_put(fdf->mlx, fdf->win, 0, 0, 16777215, "Usage:");
// 	// mlx_string_put(ptr->mlx, ptr->win, 0, 20, 16711680, "ESC to exit");
// 	// mlx_string_put(ptr->mlx, ptr->win, 0, 40, 16739840, "ARROWS to move");
// 	// mlx_string_put(ptr->mlx, ptr->win, 0, 60, 15924992,
// 	// 	"Press 'O' to 1-st projection");
// 	// mlx_string_put(ptr->mlx, ptr->win, 0, 80, 3269888,
// 	// 	"Press 'P' or 'L' to 2-nd projection");
// 	// mlx_string_put(ptr->mlx, ptr->win, 0, 100, 40447,
// 	// 	"Press 'C' to go to change projection");
// 	// mlx_string_put(ptr->mlx, ptr->win, 0, 120, 786687,
// 	// 	"Press 'NUM_PLUS' or 'NUM_MINUS' to magic zoom");
// 	// mlx_string_put(ptr->mlx, ptr->win, 0, 140, 8847615,
// 	// 	"Press 'PAGE_UP' or 'PAGE_DOWN' to change height");
// 	mlx_destroy_image(fdf->mlx, fdf->image);
// }

void ft_draw(t_fdf *fdf)
{
    fdf->image = mlx_new_image(fdf->mlx, WIDHT, HEIGHT);
	fdf->simage = mlx_get_data_addr(fdf->image, &fdf->bits_per_pixel, &fdf->size_line, &fdf->endian);
    
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->simage, 0, 0);

        // ft_mlx(fdf);
}

