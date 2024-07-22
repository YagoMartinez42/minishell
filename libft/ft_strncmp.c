/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:44:12 by samartin          #+#    #+#             */
/*   Updated: 2024/01/11 14:25:23 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Compares the first 'n' characters of two strings 's1' and `s2` and returns
 * the difference between the first differing characters, or 0 if the strings
 * are equal.
 * 
 * @param s1 A constant character pointer, the first string to be compared.
 * @param s2 A constant character pointer, the second string that we want to
 * compare with `s1`.
 * @param n The maximum number of characters to compare between the two strings.
 * The return will show they are equal if the difference occurs after that
 * character.
 * 
 * @return an integer value. If any characters before the nth are not equal, the
 * function will return the difference between their ASCII values at the
 * position where they were no longer equal.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && i < n)
		i++;
	if (s1[i] != s2[i] && i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
