/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:34:22 by maemran           #+#    #+#             */
/*   Updated: 2024/09/01 19:21:13 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		if (big[i + j] == little[0])
		{
			while (little[j] == big[i + j] && (i + j) < len)
			{
				if (little[j + 1] == '\0')
					return ((char *)(big + i));
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*big;
	char	*little;
	char	*ptr;

	big = "abcdefgh";
	little = "abc";
	ptr = ft_strnstr(big, little, 3);
	printf("%s",ptr);
}
*/
