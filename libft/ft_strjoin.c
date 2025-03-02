/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:50:06 by maemran           #+#    #+#             */
/*   Updated: 2025/02/27 15:24:43 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		length;
	int		j;

	length = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	string = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (string == NULL)
		return (NULL);
	while (s1[length] != '\0')
	{
		string[length] = s1[length];
		length++;
	}
	while (s2[j] != '\0')
	{
		string[length + j] = s2[j];
		j++;
	}
	string[j + length] = '\0';
	return (string);
}
/*
int	main(void)
{
	char	*s1;
	char	*s2;
	char	*s3;

	s1 = "mohammad";
	s2 = " ali ";
	s3 = "emran";
	printf("%s", ft_strjoin(ft_strjoin(s1, s2), s3));
}
*/
