/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:21:07 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/17 20:02:11 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Auxiliar function to check if the variable is a question mark and get
 * the content
 * @param **name As a parameter it receives a pointer to the name
 * @param **content As a parameter it receives a pointer to the content
*/
static void	expand_check(char **name, char **content)
{
	if (!name)
		error_exit(101);
	if (**name == '?')
		*content = get_str_exit_code();
	else
		*content = find_var(*name);
	if (!*content)
	{
		*content = ft_calloc(1, sizeof(char));
		if (!*content)
			error_exit(101);
	}
}

/**
* @brief Function to expand variables
* @param *str As a parameter it receives a pointer to the string
* @return It returns the string with the expanded variable
*/
char	*expand_vars(char *str)
{
	char	*name;
	char	*content;
	int		name_len;
	int		position;

	if (!ft_strchr(str, '$'))
		return (str);
	position = check_dollar(str, 0);
	while (position >= 0 && str[position])
	{
		name_len = var_size(&str[position + 1]);
		name = ft_substr(str, position + 1, name_len);
		expand_check(&name, &content);
		str = join_parts(str, content, &position, name_len);
		if (name)
			free(name);
		if (content)
			free(content);
		position = check_dollar(str, position);
	}
	return (str);
}
