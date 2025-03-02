/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:57:55 by maemran           #+#    #+#             */
/*   Updated: 2024/09/07 19:19:01 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	length;
	size_t	i;
	size_t	dst_len;

	length = 0;
	i = 0;
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + ft_strlen(src));
	length = dst_len;
	while (length < size - 1 && src[i] != '\0')
	{
		dst[length] = src[i];
		length++;
		i++;
	}
	dst[length] = '\0';
	return (ft_strlen(src) + dst_len);
}
