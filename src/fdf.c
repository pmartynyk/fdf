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

static int ft_checkButton(int button, void *asd)
{
    (void)asd;
    if (button == 53)
        exit(0);
    if (button == 17)
        exit(0);

    return (0);
}

static int ft_close(void *param)
{
    (void)param;
    exit(0);
}

int main(int argc, char **argv)
{
    t_fdf *fdf;
    fdf = (t_fdf*)malloc(sizeof(t_fdf));

    if (argc == 2)
    {
        ft_read(argv[1], fdf);
        fdf->mlx = mlx_init();
        fdf->win = mlx_new_window(fdf->mlx, 1000, 1000, "FDF");
        mlx_hook(fdf->win, 2, 0, ft_checkButton, NULL);
        mlx_hook(fdf->win, 17, 0, ft_close, NULL);
        mlx_loop(fdf->mlx);
    }
    else
    {
        ft_printf("Error!\n");
    }

    return (0);
}