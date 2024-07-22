/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:14:10 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/17 18:29:28 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a given variable name exists in the environment variables.
 * @param name A string containing the name of an environment variable that we
 * want to check for existence in the list.
 * @return 1 if the variable is found. 0 if it is not or if the first character
 * of the name is a digit.
 */
static int	var_in_env(char *name)
{
	t_minishell	values;
	int			iter;
	int			len;

	if (ft_isdigit(name[0]))
		return (0);
	len = ft_strlen(name);
	values = ms_wideuse_values(NULL, 0);
	iter = -1;
	while (values.env[++iter])
	{
		if (!ft_strncmp(values.env[iter], name, len) \
			&& values.env[iter][len] == '=')
			return (1);
	}
	return (0);
}

/**
 * @brief Removes a line from the environment
 * @param name The name of the line to remove
*/
static void	remove_line(char *name)
{
	int			iter;
	int			target;
	int			len;
	char		**aux_env;
	t_minishell	values;

	iter = -1;
	target = -1;
	len = ft_strlen(name);
	values = ms_wideuse_values(NULL, 0);
	aux_env = ft_calloc((env_len(values.env)), sizeof(char *));
	while (values.env[++iter])
	{
		if (!ft_strncmp(values.env[iter], name, len)
			&& values.env[iter][len] == '=')
			free(values.env[iter]);
		else
			aux_env[++target] = values.env[iter];
	}
	free(values.env);
	ms_wideuse_values(aux_env, ENV);
}

/**
 * @brief Recreating the unset command
 * @param args The list of arguments. Only the first one is considered, the
 * rest are ignored if any.
*/
void	ft_unset(t_list *args)
{
	if (args && args->content && var_in_env(args->content))
		remove_line(args->content);
}
