/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:31:34 by samartin          #+#    #+#             */
/*   Updated: 2023/06/29 11:54:02 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Searches for a character in a string in reverse order from the end point and
 * returns a pointer to the first (last) occurrence of the character or NULL if
 * it is not found.
 * 
 * @param s A pointer to a constant character string that we want to search for
 * the character c.
 * @param c An integer representing the ASCII value of a character that we are
 * searching for in the string s.
 * 
 * @return A pointer to the last occurrence of the character. If the character
 * is not found, it returns a null pointer.
 */
char	*ft_strrchr(const char *s, int c)
{
	int	pos;

	pos = 0;
	while (s[pos] != 0)
		pos++;
	while (pos >= 0)
	{
		if (s[pos] == (char)c)
			return ((char *)s + pos);
		pos--;
	}
	return (0);
}
