/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 19:49:35 by ggrimes           #+#    #+#             */
/*   Updated: 2019/01/10 19:52:21 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_atoi(const char *str)
{
	size_t			i;
	int				sign;
	unsigned long	num;
	int				num_bit;

	i = 0;
	sign = 1;
	num = 0;
	num_bit = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i++] - 48;
		if (num > 9223372036854775807ULL
				|| (num < 9223372036854775807ULL && ++num_bit >= 20))
			return (sign == 1 ? -1 : 0);
	}
	return (sign * num);
}
