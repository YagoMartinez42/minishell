/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:17:11 by samartin          #+#    #+#             */
/*   Updated: 2024/04/05 16:24:14 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Searches for a specific character in a given memory block.
 * 
 * @param s A pointer to the memory area to be searched. It points to the start
 * of the memory block where the search will be performed.
 * @param c The character that we are searching for within the memory block 's'.
 * It is of type int because it can represent any character value as well as the
 * special value 'EOF'.
 * @param n The number of bytes to search within the memory block starting from
 * the memory address 's'.
 * 
 * @return A pointer to the first occurrence of the character 'c' in the memory
 * block pointed to by 's'. If the character is found within the first 'n'
 * bytes, a pointer to that location is returned. If the character is not found,
 * the function returns a null pointer (0).
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	pos;

	pos = 0;
	while (pos < n)
	{
		if (((unsigned char *)s)[pos] == (unsigned char)c)
			return ((void *)(s + pos));
		pos++;
	}
	return (0);
}
