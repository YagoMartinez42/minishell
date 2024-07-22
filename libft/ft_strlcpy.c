/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:06:24 by samartin          #+#    #+#             */
/*   Updated: 2024/04/06 17:11:42 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Copies a string from src to dst with a maximum size of `dstsize` and returns
 * the length of the source string.
 * 
 * @param dst A pointer to the destination string where the copied string will
 * be stored.
 * @param src The source string that needs to be copied. It is of type const
 * char*, which means it cannot be modified by the function.
 * @param dstsize The size of the destination buffer dst. It specifies the
 * maximum number of characters that can be copied from the source string src
 * to the destination string dst, including the null terminator.
 * 
 * @return the length of the source string src.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	pos;

	pos = 0;
	while (dstsize && (src[pos] != 0) && (pos < dstsize - 1))
	{
		dst[pos] = src[pos];
		pos++;
	}
	if (dstsize > 0)
		dst[pos] = 0;
	while (src[pos] != 0)
		pos++;
	return (pos);
}
