/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:15:15 by amarquez          #+#    #+#             */
/*   Updated: 2026/02/04 12:15:16 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_spaces_and_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ft_safe_atoi(const char *str, int *result)
{
	long	temp;
	int		sign;
	int		i;
	int		digit;

	temp = 0;
	i = skip_spaces_and_sign(str, &sign);
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		digit = str[i] - '0';
		if (sign == 1 && (temp > (INT_MAX - digit) / 10))
			return (0);
		if (sign == -1 && (-temp < (INT_MIN + digit) / 10))
			return (0);
		temp = temp * 10 + digit;
		i++;
	}
	*result = sign * temp;
	return (1);
}
