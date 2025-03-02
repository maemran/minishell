/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:34:25 by maemran           #+#    #+#             */
/*   Updated: 2024/09/04 18:54:38 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int	length;

	length = 0;
	if (n < 0)
	{
		length = 1;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

static char	*process(int n, char *string, int index)
{
	int	mod;

	mod = n;
	if (n < 0)
	{
		n = -n;
		string[0] = '-';
		mod = -mod;
	}
	while (mod > 0)
	{
		string[index - 1] = (mod % 10) + 48;
		mod = mod / 10;
		index--;
	}
	return (string);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		index;
	int		length;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	index = get_len(n);
	string = malloc(index + 1);
	if (string == NULL)
		return (NULL);
	length = get_len(n);
	string = process(n, string, index);
	string[length] = '\0';
	return (string);
}
/*
int	main(void)
{
	printf("%s", ft_itoa(-2147483648));
}
*/
