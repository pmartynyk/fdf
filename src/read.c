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

static int	ft_get_dec(char c)
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

static int	ft_color_convert(char *line)
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
		if ((line[i] >= 65 && line[i] <= 70) ||
		(line[i] >= 97 && line[i] <= 102))
		{
			res += ft_get_dec(line[i]) * pow(16, len);
			len--;
		}
		i++;
	}
	if (res < 0 || res > 16777215)
		ERROR("Error color!\n");
	return (res);
}

static int	ft_color(char *line, int num)
{
	int res;

	while (*line && *line != ',')
		line++;
	if (*line != ',' && num == 0)
		res = ft_color_convert("0x8e09c6");
	else if (*line != ',' && num > 0)
		res = ft_color_convert("0xffff00");
	else if (*line != ',' && num < 0)
		res = ft_color_convert("0x00c900");
	else
	{
		line++;
		res = ft_color_convert(line);
	}
	return (res);
}

static void	ft_fill_map(char *line, t_fdf *fdf, int i)
{
	int		num;
	int		k;
	char	**tmp_map;

	if (fdf->mapLength == 0)
		fdf->mapLength = ft_count_length(line);
	if (fdf->mapLength == ft_count_length(line))
	{
		fdf->map[i] = (t_point *)malloc(sizeof(t_point) * fdf->mapLength + 1);
		k = 0;
		tmp_map = ft_strsplit(line, 32);
		while (k < fdf->mapLength)
		{
			num = ft_atoi(tmp_map[k]);
			fdf->map[i][k].x = (double)i;
			fdf->map[i][k].y = (double)k;
			fdf->map[i][k].z = (double)num;
			fdf->map[i][k].color = ft_color(tmp_map[k], num);
			k++;
		}
		ft_free(tmp_map);
	}
	else
		ERROR("Error. Wrong line length.");
}

void		ft_read(char *file, t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fdf->mapHeight = ft_count_height(file);
	fdf->map = (t_point **)malloc(sizeof(t_point *) * fdf->mapHeight + 1);
	fd = ft_checkfile(file);
	while (get_next_line(fd, &line) > 0)
	{
		ft_fill_map(line, fdf, i);
		free(line);
		i++;
	}
}
