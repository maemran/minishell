/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_two_d_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:46:14 by maemran           #+#    #+#             */
/*   Updated: 2025/04/14 09:57:13 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_two_d(char **array)
{
	char	**new_array;
	int		i;

	i = 0;
	if (!array)
		return (NULL);
	new_array = malloc(sizeof(char *) * (ft_two_d_len(array) + 1));
	if (new_array == NULL)
		return (NULL);
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		if (new_array[i] == NULL)
		{
			ft_free_tow_d_array(new_array);
			return (NULL);
		}
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
