/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:49:16 by maemran           #+#    #+#             */
/*   Updated: 2024/09/03 16:07:28 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (s == NULL && d == NULL)
		return (NULL);
	if (s >= d)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
		return (d);
	}
	else if (s < d)
	{
		i = n;
		while (i-- > 0)
			d[i] = s[i];
	}
	return (d);
}
/*
int	main(void)
{
	const char	src[100] = "emran";
	char		*ans;

	ans = (char *)ft_memmove((char *)(src) + 3, src, 3);
	printf ("%s", ans);
}
*/
