/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:25:17 by samartin          #+#    #+#             */
/*   Updated: 2023/05/26 15:50:55 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * The function `ft_bzero` sets a block of memory to zero.
 * 
 * @param s A void pointer to the memory location that needs to be zeroed out.
 * @param n The number of bytes to be set to zero in the memory block.
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*mempoint;

	mempoint = s;
	while (n > 0)
	{
		*mempoint = 0;
		mempoint++;
		n--;
	}
}
