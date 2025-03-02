/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:06:21 by maemran           #+#    #+#             */
/*   Updated: 2024/09/09 16:55:18 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*x;
	t_list	*n;

	if (*lst == NULL)
		return ;
	x = *lst;
	while (x != NULL)
	{
		n = x->next;
		del(x->content);
		free(x);
		x = n;
	}
	*lst = NULL;
}
