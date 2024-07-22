/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:31:07 by samartin          #+#    #+#             */
/*   Updated: 2023/08/09 17:48:52 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/**
 * Delete the content of a linked list node if a function was passed, then free
 * the node. It doesn't consider removing it from the list links, it is managed
 * as an already isolated node.
 *  
 * @param lst a pointer to the element.
 * @param del the content deletion function, takes a void pointer.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		if (del)
			del(lst->content);
		free(lst);
	}
}
