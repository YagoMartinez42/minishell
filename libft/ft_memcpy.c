/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:47:29 by samartin          #+#    #+#             */
/*   Updated: 2023/06/29 12:56:37 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Copies a block of memory from src to dst. It assumes both memory spaces are
 * reserved with at least 'n' size.
 * 
 * @param dst The destination memory address where the data will be copied to.
 * @param src The source memory address from where the data will be copied.
 * @param n The number of bytes to be copied from the source location to the
 * destination location.
 * 
 * @return A void type pointer to the start of the destination memory block.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ret;

	if (dst == NULL && src == NULL)
		return (NULL);
	ret = dst;
	while (n > 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst++;
		src++;
		n--;
	}
	return (ret);
}
