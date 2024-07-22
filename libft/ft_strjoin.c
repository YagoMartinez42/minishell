/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:10:11 by samartin          #+#    #+#             */
/*   Updated: 2023/05/26 15:54:20 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Concatenates two strings and returns a new string.
 * 
 * @param s1 A pointer to a constant string that will be the first part of the
 * concatenated string.
 * @param s2 A pointer to a constant character string that will be concatenated
 * to the end of s1 to create a new string.
 * 
 * @return A pointer to a newly allocated string that is the concatenation of
 * the two input strings. If either s1 or s2 is NULL, the function returns NULL.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	len1;
	unsigned int	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (str)
	{
		ft_strlcpy (str, s1, len1 + 1);
		ft_strlcat (str, s2, (len1 + len2 + 1));
	}
	return (str);
}
