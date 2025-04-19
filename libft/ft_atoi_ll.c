/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 08:15:35 by maemran           #+#    #+#             */
/*   Updated: 2025/04/13 09:37:58 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	under_over_flow_check(const char *nptr, int *i, int *sign)
{
	*i = 0;
	while ((nptr[*i] >= 9 && nptr[*i] <= 13) || nptr[*i] == 32)
		(*i)++;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (nptr[*i] < '0' || nptr[*i] > '9')
		return (0);
	return (1);
}

int	ft_atoi_ll(const char *nptr, long long *result)
{
	int			i;
	int			sign;
	long long	num;
	int			digit;

	*result = 0;
	sign = 1;
	num = 0;
	if (!under_over_flow_check(nptr, &i, &sign))
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		digit = nptr[i] - '0';
		if (sign == 1 && (num > (LLONG_MAX - digit) / 10))
			return (0);
		if (sign == -1 && (-num < (LLONG_MIN + digit) / 10))
			return (0);
		num = num * 10 + digit;
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	*result = num * sign;
	return (1);
}
