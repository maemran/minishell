/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_two_d_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:53:42 by maemran           #+#    #+#             */
/*   Updated: 2025/04/14 09:55:34 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_two_d_print(char **array)
{
	int		length;

	length = 0;
	while (array[length])
	{
		printf("%s\n", array[length]);
		length++;
	}
}
