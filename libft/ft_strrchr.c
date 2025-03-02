/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:35:27 by maemran           #+#    #+#             */
/*   Updated: 2025/02/21 20:47:37 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length] != '\0')
		length++;
	return (length);
}

char	*ft_strrchr(const char *s, int c)
{
	int				length;
	unsigned char	uc;

	length = ft_strlen(s);
	uc = (unsigned char)c;
	while (length >= 0)
	{
		if ((unsigned char)s[length] == uc)
		{
			return ((char *)(s + length));
		}
		length--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	printf("%s", ft_strrchr("ssss $PWD fwew\n",'$'));
// }
