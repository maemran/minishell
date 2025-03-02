/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:48:25 by maemran           #+#    #+#             */
/*   Updated: 2024/09/04 11:52:49 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	length;

	length = 0;
	while (s[length] != 0)
	{
		ft_putchar_fd(s[length], fd);
		length++;
	}
}
/*
int	main(void)
{
	ft_putstr_fd("mohammad",1);
}
*/
