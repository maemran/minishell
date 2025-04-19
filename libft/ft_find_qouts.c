/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_qouts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:54:20 by maemran           #+#    #+#             */
/*   Updated: 2025/04/12 23:53:02 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_qouts(char const *s, int i, int x)
{
	int	j;
	int	f;

	f = x;
	j = i + 1;
	while (s[j++])
	{
		if (s[x] == '"')
		{
			if (s[j] == '"')
			{
				f = j;
				break ;
			}
		}
		else if (s[x] == '\'')
		{
			if (s[j] == '\'')
			{
				f = j;
				break ;
			}
		}
	}
	return (f);
}
