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

static int ft_checkfile(char *file)
{
    int fd;

    fd = 0;
    if (!(ft_strstr(file, ".fdf")))
    {
        ft_printf("Invalid file\n");
        exit(0);
    }
    else if ((fd = open(file, O_DIRECTORY)) >= 0)
    {
        ft_printf("Invalid file\n");
        exit(0);
    }
    else if ((fd = open(file, O_RDONLY)) < 0)
    {
        ft_printf("Invalid file\n");
        exit(0);
    }
    return (fd);
}

static int ft_countword(char *str)
{
    int i;
    int cnt;

    i = 0;
    cnt = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
            cnt++;
        i++;
    }
    return (cnt);
}

static void ft_fillMap(char *line, t_fdf *fdf, int i)
{
    int num;
    int k;

    fdf->mapLength = ft_countword(line);
    fdf->map[i] = (t_point *)malloc(sizeof(t_point) * fdf->mapLength + 1);
    k = 0;
    while (*line)
    {
        if (*line != ' ')
        {
            num = ft_atoi(line);
            fdf->map[i][k].z = num;
            line += ft_intlen(num);
            k++;
        }
        else
            line++;
    }
}

static int ft_countHeight(char *file)
{
    int i;
    int fd;
    char *line;

    i = 0;
    fd = ft_checkfile(file);
    while (get_next_line(fd, &line) > 0)
        i++;
    close(fd);
    return (i);
}

void ft_read(char *file, t_fdf *fdf)
{
    int fd;
    char *line;
    int i;

    i = 0;
    fdf->mapHeight = ft_countHeight(file);
    fdf->map = (t_point **)malloc(sizeof(t_point*) * fdf->mapHeight + 1);
    fd = ft_checkfile(file);
    while (get_next_line(fd, &line) > 0)
    {
        ft_fillMap(line, fdf, i);
        i++;
    }

    // int x = 0;
    // int y = 0;
    // while (x < fdf->mapHeight)
    // {
    //     y = 0;
    //     while (y < fdf->mapLength)
    //     {
    //         ft_printf("%d ", fdf->map[x][y].z);
    //         y++;
    //     }
    //     ft_printf("\n");
    //     x++;
    // }

}
