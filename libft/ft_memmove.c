/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:28:48 by samartin          #+#    #+#             */
/*   Updated: 2023/06/29 12:55:30 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Copies 'n' bytes from the memory area pointed to by 'src' to the memory area
 * pointed to by 'dst', handling overlapping memory areas correctly.
 * 
 * @param dst The destination memory address where the data will be copied to.
 * @param src The source memory address from where the data will be copied.
 * @param n The number of bytes to be copied from the source memory area to the
 * destination memory area.
 * 
 * @return A void type pointer to the start of the destination memory block.
 */
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int	i;

	if (src == NULL && dst == NULL)
		return (NULL);
	if (dst > src && dst < (src + n))
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)n)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}
