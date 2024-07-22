/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:48:23 by samartin          #+#    #+#             */
/*   Updated: 2023/05/16 11:50:46 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Copies the contents of a source string to a destination string.
 * 
 * @param dest A pointer to the destination string where the copied string will
 * be stored. It should have enough reserved space to hold the entire source
 * string, including the null terminator.
 * @param src The source string to be copied.
 * @return A pointer to the destination string dest.
 */
char	*ft_strcpy(char *dest, char *src)
{
	int	pos;

	if (dest && src)
	{
		pos = -1;
		while (src[++pos] != 0)
			dest[pos] = src[pos];
		dest[pos] = src[pos];
	}
	return (dest);
}
