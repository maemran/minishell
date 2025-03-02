/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:01:23 by maemran           #+#    #+#             */
/*   Updated: 2024/09/04 20:21:05 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	length;
	char			*string;

	length = 0;
	string = malloc(ft_strlen(s) + 1);
	if (string == NULL)
		return (NULL);
	while (s[length] != '\0')
	{
		string[length] = f(length, s[length]);
		length++;
	}
	string[length] = '\0';
	return (string);
}
