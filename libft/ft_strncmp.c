/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:33:00 by maemran           #+#    #+#             */
/*   Updated: 2025/03/31 16:10:33 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			length;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	length = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	if (!s1 || !s2)
		return (2);
	while ((ptr1[length] != '\0' || ptr2[length] != '\0') && length < n)
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
	printf("%i", ft_strncmp("1234", "1235", -2));
	printf("%i", strncmp("1234", "1235", -2));
}
*/
