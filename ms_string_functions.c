/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_string_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:31:24 by samartin          #+#    #+#             */
/*   Updated: 2024/07/22 16:33:28 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if a character is a whitespace
 * @param c Character to check
*/
int	is_whitespace(char c)
{
	char	*ws;

	ws = " \t\v\n\f\r";
	while (*ws)
	{
		if (c == *ws)
			return (1);
		ws++;
	}
	return (0);
}

/**
 * @brief Skip all whitespaces in a string
 * @param str String to check
*/
size_t	skip_whitespace(char *str)
{
	size_t	pos;

	pos = 0;
	while (is_whitespace(str[pos]))
		pos++;
	return (pos);
}

/**
 * @brief Check if a string is a number
 * @param str String to check
 * @return 1 if the string is a number, 0 otherwise
*/
int	str_is_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
