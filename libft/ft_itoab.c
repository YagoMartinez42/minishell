/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:14:48 by samartin          #+#    #+#             */
/*   Updated: 2024/01/22 17:10:08 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Converts an long integer number to a string representation in a given base.
 * Dropping recursively each digit inside its position in the string.
 * 
 * @param str A pointer to a character array that is the string where the
 * digits will be dropped.
 * @param n The number that we want to convert to a character representation.
 * @param base The number system base in which the number should be converted.
 * It can have a value between 2 and 36.
 * 
 * @return the index of the last character that was added to the string.
 */
static int	drop_d(char *str, long n, int base)
{
	int		idx;
	char	*base_symbols;

	idx = 0;
	base_symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (n >= base)
		idx = drop_d(str, n / base, base) + 1;
	str[idx] = base_symbols[n % base];
	return (idx);
}

/**
 * Converts a long integer into a string representation in a specified base.
 * first malloc is done reserving the space that would be needed for a 64-bit
 * number in binary base, plus sign and string terminator. When the string is
 * set, then is copied reserving the exact size and freeing the previous space. 
 * 
 * @param n A long integer value that we want to convert to a string.
 * @param base The base of the number system being used. It determines the
 * amount of symbols used to represent numbers. Allowing up to 'Z' covers any
 * range between 2 and 36, inclusive.
 * 
 * @return A pointer to a character array (string) that represents the given
 * number in the specified base.
 */
char	*ft_itoab(long n, int base)
{
	char	*nb_as_str;
	char	*aux;
	int		dig;

	if (base > 36 || base < 2)
		return (NULL);
	nb_as_str = malloc (66 * sizeof(char));
	if (!nb_as_str)
		return (0);
	dig = 0;
	if (n < 0)
	{
		*nb_as_str = '-';
		n = -n;
		dig++;
	}
	dig += drop_d (nb_as_str + dig, n, base);
	nb_as_str[dig + 1] = '\0';
	aux = nb_as_str;
	nb_as_str = malloc ((dig + 2) * sizeof(char));
	ft_strcpy(nb_as_str, aux);
	free(aux);
	if (!nb_as_str)
		return (0);
	return (nb_as_str);
}
