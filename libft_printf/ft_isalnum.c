/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:05:10 by pmartyny          #+#    #+#             */
/*   Updated: 2018/10/25 17:07:35 by pmartyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int symb)
{
	if ((symb >= 48 && symb <= 57)
			|| (symb >= 65 && symb <= 90)
			|| (symb >= 97 && symb <= 122))
		return (1);
	else
		return (0);
}
