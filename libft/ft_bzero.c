/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:49:16 by maemran           #+#    #+#             */
/*   Updated: 2024/09/01 14:59:24 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	length;
	char	*ptr;

	length = 0;
	ptr = (char *)s;
	while (length < n)
	{
		ptr[length] = '\0';
		length++;
	}
}
