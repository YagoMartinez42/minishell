/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:41:02 by samartin          #+#    #+#             */
/*   Updated: 2024/01/11 14:29:59 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Takes a string 's1' as input and returns a dynamically allocated copy of it.
 * 
 * @param s1 The input string that we want to duplicate.
 * 
 * @return A pointer to the newly allocated string, duplicate of 's1'.
 */
char	*ft_strdup(const char *s1)
{
	unsigned int	len;
	unsigned int	i;
	char			*s2;

	len = 0;
	while (s1[len])
		len++;
	s2 = malloc(len + 1 * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
