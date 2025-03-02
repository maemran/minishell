/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:04:19 by maemran           #+#    #+#             */
/*   Updated: 2024/09/01 20:08:06 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		length;
	char		*ptr1;
	const char	*source;

	length = 0;
	ptr1 = (char *)dest;
	source = (const char *)src;
	if (!ptr1 && !source)
		return (NULL);
	while (length < n)
	{
		ptr1[length] = source[length];
		length++;
	}
	return (ptr1);
}
/*
int	main(void)
{
	char		dest[10] = "";
	const char	*src = "";

	printf("%s\n", (char * )ft_memcpy(dest, src, 3));
	printf("%s\n", (char * )memcpy(dest, src, 3));
	return (0);
}
*/
