/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:42:31 by pmartyny          #+#    #+#             */
/*   Updated: 2019/09/12 13:42:33 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int ft_checkfile(char *argv)
{
    int fd;

    fd = 0;
    if (!(ft_strstr(argv, ".fdf")))
    {
        ft_printf("Invalid file\n");
        exit(0);
    }
    else if ((fd = open(argv, O_DIRECTORY)) >= 0)
    {
        ft_printf("Invalid file\n");
        exit(0);
    }
    else if ((fd = open(argv, O_RDONLY)) < 0)
    {
        ft_printf("Invalid file\n");
        exit(0);
    }
    return (fd);
}

void ft_read(char *argv, t_map *map)
{
    (void)map;
    int fd;

    fd = ft_checkfile(argv);
}

