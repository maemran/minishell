/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:50:08 by maemran           #+#    #+#             */
/*   Updated: 2024/09/01 19:10:28 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				length;
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	length = 0;
	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	while (length < n)
	{
		if (ptr1[length] != ptr2[length])
			return (ptr1[length] - ptr2[length]);
		length++;
	}
	return (0);
}
/*
int	main(void)
{
	printf("%i\n",ft_memcmp("mohammad", "Mohammad", 4));
}
*/
