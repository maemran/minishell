/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:19:40 by maemran           #+#    #+#             */
/*   Updated: 2024/09/01 19:16:45 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	length;
	char	*ptr;

	length = 0;
	ptr = (char *)s;
	while (length < n)
	{
		ptr[length] = c;
		length++;
	}
	return (ptr);
}
/*
int	main(void)
{
	char	s[] = "mohammad";
	char	*s1;

	s1 = (char *)ft_memset(s,'M',8);
	printf("%s",s1);
}
*/
