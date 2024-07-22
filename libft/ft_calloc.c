/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:17:40 by samartin          #+#    #+#             */
/*   Updated: 2023/05/26 15:49:37 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Allocates memory for an array of elements and initializes the memory to zero.
 * 
 * @param count The number of elements to allocate memory for.
 * @param size The size in bytes of each element to be allocated.
 * 
 * @return A pointer to the allocated memory block, or NULL if the allocation
 * fails.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void		*startp;
	long long	space;

	space = size * count;
	if (space == 1 && size != 1)
		return (NULL);
	startp = malloc (space);
	if (startp == NULL)
		return (NULL);
	while (space > 0)
	{
		((char *)startp)[space - 1] = '\0';
		space--;
	}
	return (startp);
}
