/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanzas- <dlanzas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:21:07 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/17 12:27:00 by dlanzas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Takes in the length of a variable name and a position in the
 * environment  * string array (count), and returns a string containing the
 * expanded value of the variable if the name matches.
 * @param  name: The name of the variable to be checked to exist at the 'count'
 * position.
 * @param  name_len: The length of the name given, to skip it and take only the
 * value after the '='.
 * @param  count: The position of the variable in the table.
 * @return The expanded string.
 */
char	*retrieve_var(char *name, int name_len, int count)
{
	int			i;
	char		*expanded;
	t_minishell	values;

	values = ms_wideuse_values(NULL, 0);
	expanded = NULL;
	if (ft_strncmp((values.env[count]), name, name_len) == 0 \
	&& values.env[count][name_len] == '=')
	{
		expanded = ft_calloc((ft_strlen(values.env[count]) - name_len), 1);
		if (!expanded)
			error_exit(101);
		i = -1;
		while (values.env[count][(++i) + name_len + 1])
			expanded[i] = values.env[count][i + name_len + 1];
		expanded[i] = '\0';
	}
	return (expanded);
}

/**
 * @brief Searches for a variable in the cloned environment and returns its
 * value in a newly allocated (inside 'var_found) string.
 * @param name Name of the environment variable to find, with the '$' from the
 * call removed.
 * @return The value of the environment variable, al characters after the '=' up
 * to the terminator '\0'.
 */
char	*find_var(char *name)
{
	int			name_len;
	int			count;
	char		*expanded;
	t_minishell	values;

	name_len = ft_strlen(name);
	count = -1;
	expanded = NULL;
	values = ms_wideuse_values(NULL, 0);
	while (name_len && !expanded && values.env[++count])
		expanded = retrieve_var(name, name_len, count);
	if (!expanded)
	{
		expanded = ft_calloc(2, sizeof(char));
		if (!expanded)
			error_exit(101);
		if (!name_len)
			*expanded = '$';
	}
	return (expanded);
}

/**
* @brief Function to calculate de lenght of the name of the variable
* @param *str As a parameter it receives a pointer to the string
* @return It returns the lenght of the name
*/
int	var_size(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !is_whitespace(str[len]) && (ft_isalnum(str[len])
			|| str[len] == '_'))
		len++;
	if (len == 0 && *str == '?')
		len = 1;
	return (len);
}

/**
 * @brief Function to join parts of a string and obtain the expanded variable
 * @param *str As a parameter it receives a pointer to the string
 * @param *content As a parameter it receives a pointer to the content
 * @param *position As a parameter it receives a pointer to the position
 * @param name_len As a parameter it receives the length of the name
*/
char	*join_parts(char *str, char *content, int *position, int name_len)
{
	char	*aux;
	char	*third_part;

	if (!str)
		return (str);
	aux = str;
	str = ft_calloc(ft_strlen(str) + ft_strlen(content) + 2 - name_len, 1);
	if (!str)
		error_exit(101);
	aux[*position] = '\0';
	ft_strlcpy(str, aux, ft_strlen(aux) + 1);
	ft_strlcat(str, content, *position + ft_strlen(content) + 1);
	if (!str)
		error_exit(101);
	third_part = aux + *position + name_len + 1;
	*position = ft_strlen(str);
	ft_strlcat(str, third_part, ft_strlen(str) + ft_strlen(third_part) + 1);
	if (!str)
		error_exit(101);
	free(aux);
	return (str);
}
