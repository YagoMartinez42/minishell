/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:23:15 by samartin          #+#    #+#             */
/*   Updated: 2024/04/05 16:19:28 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Compares two strings and returns the ascii difference between the first
 * differing characters or 0 if there is no difference. Also returns a value as
 * if it was an empty string in case any of the two was a NULL pointer.
 * 
 * @param s1 The first string to be compared.
 * @param s2 The second string to be compared.
 * 
 * @return an integer value.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
