/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:42:49 by samartin          #+#    #+#             */
/*   Updated: 2024/04/05 16:19:03 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Searches for the first occurrence of a substring 'needle' in a string
 * 'haystack' up to a specified length 'len'. If the starting point of an
 * occurrence happens inside the 'len' limits but it has not room left for a
 * full occurrence of 'needle', it will reach the end of 'haystack' but no
 * longer looking for the 'needle'.
 * 
 * @param haystack A pointer to the string in which we want to search for the
 * 'needle' string.
 * @param needle A pointer to the substring that we are searching for within the
 * 'haystack' string.
 * @param len The maximum number of characters to search in the 'haystack'
 * string.
 * 
 * @return A pointer to the first occurrence of the 'needle' string within the
 * 'haystack' string, up to a maximum of 'len' characters. If the 'needle'
 * string is empty, it returns a pointer to the 'haystack' string. If the
 * 'needle' string is not found within the 'haystack' string, it returns NULL.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	pos1;
	unsigned int	pos2;

	if (*needle == '\0')
		return ((char *)haystack);
	pos1 = 0;
	while (pos1 < len && haystack[pos1] != 0)
	{
		pos2 = 0;
		while ((pos1 + pos2) < len && haystack[pos1 + pos2] == needle[pos2])
		{
			if (needle[pos2 + 1] == 0)
				return ((char *)&haystack[pos1]);
			pos2++;
		}
		pos1++;
	}
	return (NULL);
}
