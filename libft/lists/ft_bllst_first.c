/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bllst_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:51:37 by samartin          #+#    #+#             */
/*   Updated: 2023/04/04 12:41:05 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/**
 * Ft_bllst_first() returns the first element of a doubly linked list.
 * 
 * @param lst The last or any element of the list to get the first element of.
 * 
 * @return The first element of the list.
 */
t_bllist	*ft_bllst_first(t_bllist *lst)
{
	if (lst)
	{
		while (lst->prev)
			lst = lst->prev;
	}
	return (lst);
}
