/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:05:01 by maemran           #+#    #+#             */
/*   Updated: 2024/09/03 18:49:01 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	length;
	char	*string;

	length = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	string = malloc(len + 1);
	if (string == NULL)
		return (NULL);
	while (length < len)
	{
		string[length] = s[start + length];
		length++;
	}
	string[len] = '\0';
	return (string);
}
/*
int	main(void)
{
	//char	*s = "mohammad";
	printf("%s", ft_substr("hola", 4294967295, 0));
}
*/
