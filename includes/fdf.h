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

typedef struct s_map
{
    int x;
    int y;
    int z;
} t_map;

//read.c
void ft_read(char *argv, t_map *map);

#endif
