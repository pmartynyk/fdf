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

int main(int argc, char **argv)
{
    t_map map;
    if (argc == 2)
    {
        ft_read(argv[1], &map);
        mlx_init();
    }
    else
    {
        ft_printf("Error!\n");
    }

    return (0);
}