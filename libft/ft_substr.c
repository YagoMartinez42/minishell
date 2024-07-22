/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:46:49 by samartin          #+#    #+#             */
/*   Updated: 2024/04/06 17:34:31 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * This function returns a substring of a given string starting from a specified
 * index and with a specified length.
 * 
 * @param s The input string from which the substring will be extracted.
 * @param start The starting index of the substring to be extracted from the
 * input string.
 * @param len The length of the substring to be extracted from the input string.
 * 
 * @return A pointer to a newly allocated substring of the input string s. If s
 * is null, it returns NULL. If start is greater than or equal to the length of
 * s, it returns a pointer to a newly allocated empty string. If len is greater
 * than the length of the substring starting from start, it adjusts.
 */
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			i;
	unsigned int	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		sub = ft_calloc(1, 1);
		return (sub);
	}
	if (len > (slen - start))
		len = slen - start;
	sub = malloc ((len + 1) * (sizeof(char)));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
