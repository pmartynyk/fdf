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

static int ft_countLength(char *str)
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

static int ft_getDec(char c)
{
    int res;

    if (c == 65 || c == 97)
        res = 10;
    if (c == 66 || c == 98)
        res = 11;
    if (c == 67 || c == 99)
        res = 12;
    if (c == 68 || c == 100)
        res = 13;
    if (c == 69 || c == 101)
        res = 14;
    if (c == 70 || c == 102)
        res = 15;
    return (res);
}

int ft_colorConvert(char *line)
{
    int res;
    int i;
    int len;

    res = 0;
    i = 2;
    len = (ft_strlen(line) - 3);
    while (line[i] && len >= 0)
    {
        if (line[i] >= '0' && line[i] <= '9')
        {
            res += (line[i] - '0') * pow(16, len);
            len--;
        }
        if ((line[i] >= 65 && line[i] <= 70) || (line[i] >= 97 && line[i] <= 102))
        {
            res += ft_getDec(line[i]) * pow(16, len);
            len--;
        }
        i++;
    }
    if (res < 0 || res > 16777215)
    {
        ft_printf("Error color!\n");
        exit(0);
    }
    return (res);
}

static int ft_color(char *line, int num)
{
    int res;

    while (*line && *line != ',')
        line++;
    if (*line != ',' && num == 0)
        res = ft_colorConvert("0x8e09c6");
    else if (*line != ',' && num > 0)
        res = ft_colorConvert("0xffff00");
    else if (*line != ',' && num < 0)
        res = ft_colorConvert("0x00c900");
    else
    {
        line++;
        res = ft_colorConvert(line);
    }

    return (res);
}

static void ft_fillMap(char *line, t_fdf *fdf, int i)
{
    int num;
    int k;
    char **tmpMap;

    fdf->mapLength = ft_countLength(line);
    
    fdf->map[i] = (t_point *)malloc(sizeof(t_point) * fdf->mapLength + 1);
    k = 0;
    tmpMap = ft_strsplit(line, 32);
    while (k < fdf->mapLength)
    {
        num = ft_atoi(tmpMap[k]);
        fdf->map[i][k].x = (double)i;
        fdf->map[i][k].y = (double)k;
        fdf->map[i][k].z = (double)num;
        fdf->map[i][k].color = ft_color(tmpMap[k], num);
        k++;
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
    fdf->map = (t_point **)malloc(sizeof(t_point *) * fdf->mapHeight + 1);
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
    //         ft_printf("%d, %d | %f, %f\n", x, y, fdf->map[x][y].x, fdf->map[x][y].y);
    //         y++;
    //     }
    //     ft_printf("\n");
    //     x++;
    // }
}
