/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:13:55 by maemran           #+#    #+#             */
/*   Updated: 2024/09/04 12:28:47 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	length;

	length = 0;
	if (dst == NULL)
		return (ft_strlen(src));
	if (size == 0)
		return (ft_strlen(src));
	while (src[length] != '\0' && length < size - 1)
	{
		dst[length] = src[length];
		length++;
	}
	dst[length] = '\0';
	return (ft_strlen(src));
}
/*
int	main(void)
{
	char	s1[5];
	char	s2[] = " ";

	printf("%s\n", ft_strlcpy(s1, s2, 1));
}
*/
