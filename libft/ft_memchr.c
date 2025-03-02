/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:31:30 by maemran           #+#    #+#             */
/*   Updated: 2024/09/01 20:39:56 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	length;

	length = 0;
	while (length < n)
	{
		if (*((unsigned char *)s) == (unsigned char)c)
			return ((char *)s);
		s++;
		length++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*array1;
	char	*array2;

	// test for integers values
   // const int string[] = {1 ,3 ,4, 5};
	//int c = 3;
	//int *array = (int *)ft_memchr(string,c,sizeof(string));
	//printf ("%i\n",array[0]);
	//printf ("%i\n",array[1]);
	//printf ("%i\n\n",array[2]);
	//test for char values
	array1 = (char *)ft_memchr("0x7ffdc7f3b580",')', 35);
	array2 = (char *)memchr("0x7ffdc7f3b580", ')', 35);
	printf ("%s",array1);
	printf ("%s",array2);
}
*/
